// Hydrogen 2020

#include "UI/UIPooling/Public/UIPoolProvider.h"
#include "UI/UIPooling/Public/UIPoolSeed.h"

DEFINE_LOG_CATEGORY_STATIC(UIPoolProviderLog, Log, Log)

FUIPoolProvider::FUIPoolProvider()
{

}

FUIPoolProvider::FUIPoolProvider(const UObject& InOwner)
	: HasPreheated(false)
	, Owner(&InOwner)
	, NumInitialisedSeeds(0)
	, NumRequestedSeeds(0)
	, RecycleWidgetsDelegate()
{

}

void FUIPoolProvider::InitialisePreheat(const TArray<FUIPoolSeed>& InSeeds)
{
	checkf(!HasPreheated, TEXT("Cannot call preheat more than once"));
	checkf(Owner.IsValid(), TEXT("UIPoolProvider has no owner"));
	Seeds = InSeeds;

	if (UObject* StrongOwner = Owner.Get())
	{
		if (UWorld* World = StrongOwner->GetWorld())
		{
			RecycleWidgetsDelegate.BindWeakLambda(StrongOwner, [this, World = World]()
			{
				Recycle();
			});

			PreheatWidgetsDelegate.BindWeakLambda(StrongOwner, [this, World = World]()
			{
				IncrementPreheat();

				if (ShouldIncremementPreheat())
				{
					IncrementPreheat();
				}
				else
				{
					UE_LOG(UIPoolProviderLog, Log, TEXT("Finished preheating UIPool"));
					World->GetTimerManager().SetTimer(PoolProviderTickHandle, RecycleWidgetsDelegate, 0.1f, true);
				}
			});

			World->GetTimerManager().SetTimer(PoolProviderTickHandle, PreheatWidgetsDelegate, World->GetDeltaSeconds(), true);
		}

		for (const FUIPoolSeed& Seed : Seeds)
		{
			if (Seed.Class)
			{
				NumRequestedSeeds += Seed.NumToPreheat;

				if (!GetPoolForClass(Seed.Class))
				{
					if (UUIPool* NewPool = NewObject<UUIPool>(Owner.Get()))
					{
						NewPool->Initialise(Seed.Class, Seed.NumToPreheat);
						Pools.Add(NewPool);

						UE_LOG(UIPoolProviderLog, Log, TEXT("Creating pool for %s"), *Seed.Class->GetName());
					}
					else
					{
						UE_LOG(UIPoolProviderLog, Error, TEXT("Could not create pool"));
					}
				}
			}
			else
			{
				UE_LOG(UIPoolProviderLog, Error, TEXT("Could not create UIPool - Class was null"));
			}
		}
	}

	UE_LOG(UIPoolProviderLog, Log, TEXT("UIPoolPreheatStarted - preheating %i elements"), NumRequestedSeeds);
}

void FUIPoolProvider::IncrementPreheat()
{
	if (Seeds.IsValidIndex(0))
	{
		FUIPoolSeed& CurrSeed = Seeds[0];
		
		if (UUIPool* PoolForSeed = GetPoolForClass(CurrSeed.Class))
		{
			if (PoolForSeed->ExpandPool())
			{
				--CurrSeed.NumToPreheat;
			}
		}
	
		if (CurrSeed.NumToPreheat <= 0)
		{
			Seeds.RemoveAt(0);
		}

		++NumInitialisedSeeds;
	}


#if !UE_BUILD_SHIPPING
	if (NumInitialisedSeeds % 10 == 0)
	{
		UE_LOG(UIPoolProviderLog, Log, TEXT("UIPool Preheat (%i/%i)"), NumInitialisedSeeds, NumRequestedSeeds);
	}
#endif //!UE_BUILD_SHIPPING
}

bool FUIPoolProvider::ShouldIncremementPreheat() const
{
	return Seeds.Num() != 0;
}

void FUIPoolProvider::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObjects(Pools);
}

UUIPool* FUIPoolProvider::GetPoolForClass(const TSubclassOf<UUserWidget>& InClass)
{
	const int8 FoundPool = Pools.IndexOfByPredicate([InClass](UUIPool* Pool)
	{
		return Pool->PoolClass == InClass;
	});

	if (FoundPool != INDEX_NONE)
	{
		return Pools[FoundPool];
	}

	return nullptr;
}

void FUIPoolProvider::Recycle()
{
	for(UUIPool* Pool : Pools)
	{
		uint32 NumRecycledWidgets = 0;

		for(int32 i = Pool->ActiveWidgets.Num()-1; i >= 0; --i)
		{
			UUserWidget* CurrentWidget = Pool->ActiveWidgets[i];

			if (!CurrentWidget->GetCachedWidget().IsValid())
			{
				if (Pool->CanAddToInactivePool())
				{
					Pool->InactiveWidgets.Add(CurrentWidget);
				}

				Pool->ActiveWidgets.Remove(CurrentWidget);
				NumRecycledWidgets++;
			}
		}

		if (NumRecycledWidgets > 0)
		{
			UE_LOG(UIPoolProviderLog, Log, TEXT("Recycled %s (%i)"), *Pool->PoolClass->GetName(), NumRecycledWidgets);
			return;
		}
	}
}