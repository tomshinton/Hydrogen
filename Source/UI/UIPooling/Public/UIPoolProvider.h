// Hydrogen 2020

#pragma once

#include "CoreMinimal.h"

#include <Runtime/CoreUObject/Public/UObject/GCObject.h>
#include <Runtime/Engine/Classes/GameFramework/HUD.h>

#include "UI/UIPooling/Public/UIPoolProviderInterface.h"
#include "UI/UIPooling/Public/UIPool.h"

struct FUIPoolSeed;
 
class UIPOOLING_API FUIPoolProvider : public FGCObject
{
public:

	FUIPoolProvider();
	FUIPoolProvider(const UObject& InOwner);

	void InitialisePreheat(const TArray<FUIPoolSeed>& InSeeds);

	void IncrementPreheat();
	bool ShouldIncremementPreheat() const;

	//FGCObject
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override final;
	//~FGCObject
	
	template<class TWidget>
	static TWidget* NewWidget(const UObject& InOwner, const TSubclassOf<UUserWidget>& InClass)
	{
#if UIPOOLING 
		static_assert(TIsDerivedFrom<TWidget, UUserWidget>::IsDerived, "UIProviders can only return UUserWidget types");

		if (UWorld* World = GWorld)
		{
			if (AActor* HUD = World->GetFirstPlayerController()->GetHUD())
			{
				if (IUIPoolProviderInterface* ProviderInterface = Cast<IUIPoolProviderInterface>(HUD))
				{
					return ProviderInterface->GetPoolProvider().NewWidgetInternal<TWidget>(InClass);
				}
			}
		}

		return nullptr;

#else
		return NewObject<TWidget>(const_cast<UObject*>(&InOwner), InClass);
#endif //UIPOOLING
	}

private:

	template<class TWidget>
	TWidget* NewWidgetInternal(const TSubclassOf<UUserWidget>& InClass)
	{
		if (UUIPool* PoolForClass = GetPoolForClass(InClass))
		{
			return PoolForClass->GetWidget<TWidget>();
		}

		return nullptr;
	}

	UUIPool* GetPoolForClass(const TSubclassOf<UUserWidget>& InClass);
	void Recycle();

	bool HasPreheated;
	TArray<FUIPoolSeed> Seeds;
	TWeakObjectPtr<UObject> Owner;

	UPROPERTY()
	TArray<UUIPool*> Pools;

	uint32 NumInitialisedSeeds;
	uint32 NumRequestedSeeds;

	FTimerDelegate PreheatWidgetsDelegate;
	FTimerDelegate RecycleWidgetsDelegate;

	FTimerHandle PoolProviderTickHandle;
};
