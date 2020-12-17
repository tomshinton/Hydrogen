#include "Runtime/Interaction/Public/InteractionComponent.h"

#include <Runtime/Camera/Public/PlayerViewInterface.h>
#include <Runtime/Collision/Public/CollisionDefs.h>
#include <Runtime/Interaction/Public/Hovering/HoverableInterface.h>
#include <Runtime/UseFramework/Public/Events/UseEvents.h>
#include <ObjectMessaging/Public/Listener/ObjectMessagingListenerInterface.h>
#include <ObjectMessaging/Public/Sender/ObjectMessagingFunctions.h>

DEFINE_LOG_CATEGORY_STATIC(InteractionComponentLog, Log, Log)

namespace InteractionComponentBindings
{
	const FName UseBinding = TEXT("Use");
}

UInteractionComponent::UInteractionComponent(const FObjectInitializer& InObjectInitialiser)
	: TraceDistance(2000.f)
	, TraceParams()
	, TraceHandle()
	, TraceDelegate(FTraceDelegate::CreateUObject(this, &UInteractionComponent::OnTraceComplete))
	, CanTrace(true)
	, CachedViewInterface()
	, CurrentHover()
	, IsUsing(false)
	, UseTime(0.f)
	, TapLength(0.1)
{
	TraceParams.AddIgnoredActor(GetOwner());

	PrimaryComponentTick.bStartWithTickEnabled = true;
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bAllowTickOnDedicatedServer = false;
}

#if WITH_CLIENT_CODE
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetNetMode() != NM_DedicatedServer)
	{
		if (IPlayerViewInterface* PlayerViewInterface = GetOwner()->GetInterface<IPlayerViewInterface>())
		{
			CachedViewInterface = *PlayerViewInterface;
		}
		else
		{
			UE_LOG(InteractionComponentLog, Error, TEXT("Could not find a valid PlayerViewInterface on %s"), *GetOwner()->GetName())
		}
	}
}
#endif //WITH_CLIENT_CODE

#if WITH_CLIENT_CODE
void UInteractionComponent::SetupComponentInputBindings(UInputComponent& PlayerInputComponent)
{
	Super::SetupComponentInputBindings(PlayerInputComponent);

	PlayerInputComponent.BindAction(InteractionComponentBindings::UseBinding, IE_Pressed, this, &UInteractionComponent::StartUse);
	PlayerInputComponent.BindAction(InteractionComponentBindings::UseBinding, IE_Released, this, &UInteractionComponent::EndUse);
}
#endif //WITH_CLIENT_CODE

void UInteractionComponent::StartUse()
{
	if (CurrentHover.IsValid())
	{
		if (IObjectMessagingListenerInterface* ListenerInterface = CurrentHover->GetActor()->GetInterface<IObjectMessagingListenerInterface>())
		{
			ObjectMessagingFunctions::SendMessage<FOnStartUse>(*ListenerInterface, FOnStartUse([WeakThis = TWeakObjectPtr<UInteractionComponent>(this)]()
			{
				if (UInteractionComponent* StrongThis = WeakThis.Get())
				{
					return StrongThis->UseTime;
				}

				return 0.f;
			}));
		}

		IsUsing = true;
	}
}

void UInteractionComponent::EndUse()
{
	if (CurrentHover.IsValid() && IsUsing)
	{
		IsUsing = false;
		
		if (IObjectMessagingListenerInterface* ListenerInterface = CurrentHover->GetActor()->GetInterface<IObjectMessagingListenerInterface>())
		{
			ObjectMessagingFunctions::SendMessage<FOnEndUse>(*ListenerInterface, UseTime <= TapLength ? 0.f : UseTime);
		}
	}

	UseTime = 0.f;
}

void UInteractionComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (CanTrace)
	{
		UpdateHover(DeltaTime);
	}

	if (IsUsing)
	{
		UpdateUse(DeltaTime);
	}
}

void UInteractionComponent::UpdateHover(const float InDeltaTime)
{
	//Request async trace
	if (UWorld* World = GetWorld())
	{
		const FTransform PlayerViewpoint = CachedViewInterface->GetCameraTransform();

		const FVector StartLocation = PlayerViewpoint.GetLocation();
		const FVector EndLocation = PlayerViewpoint.GetLocation() + ((PlayerViewpoint.GetRotation().Vector() * TraceDistance));

		World->AsyncLineTraceByChannel(EAsyncTraceType::Single, StartLocation, EndLocation, ECC_Interaction, TraceParams, FCollisionResponseParams::DefaultResponseParam, &TraceDelegate);
		CanTrace = false;
	}
}

void UInteractionComponent::UpdateUse(const float InDeltaTime)
{
	UseTime = FMath::Max(UseTime + InDeltaTime, 0.f);
}

void UInteractionComponent::OnTraceComplete(const FTraceHandle& InHandle, FTraceDatum& InData)
{
	ProcessData(InData);
	TraceHandle._Data.FrameNumber = 0;
}

void UInteractionComponent::ProcessData(const FTraceDatum& InTraceData)
{
	if (InTraceData.OutHits.Num() > 0)
	{
		for (const FHitResult& HitResult : InTraceData.OutHits)
		{
			ProcessHit(HitResult);
		}
	}
	else
	{
		ClearCurrentHover();
	}

	CanTrace = true;
}

void UInteractionComponent::ProcessHit(const FHitResult& InResult)
{
	if (AActor* StrongHitRes = InResult.Actor.Get())
	{
		if (IHoverableInterface* HitHoverable = StrongHitRes->GetInterface<IHoverableInterface>())
		{
			if (IsHoveringDifferentItem(*HitHoverable))
			{
				ClearCurrentHover();
				SetNewHover(*HitHoverable);
			}
		}
		else
		{
			ClearCurrentHover();
		}
	}
	else
	{
		ClearCurrentHover();
	}
}

bool UInteractionComponent::IsHoveringDifferentItem(const IHoverableInterface& InHoverable) const
{
	if (!CurrentHover.IsValid())
	{
		return true;
	}
	
	IHoverableInterface* CurrentHoverRaw = &(*CurrentHover);

	return CurrentHoverRaw != &InHoverable;
}

void UInteractionComponent::SetNewHover(IHoverableInterface& InNewHover)
{
	CurrentHover = InNewHover;
	CurrentHover->OnStartHover();
}

void UInteractionComponent::ClearCurrentHover()
{
	if (CurrentHover.IsValid())
	{
		CurrentHover->OnEndHover();

		if (IsUsing)
		{
			EndUse();
		}

		CurrentHover = TWeakInterfacePtr<IHoverableInterface>();
	}
}
