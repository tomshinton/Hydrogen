#pragma once

#include <Runtime/Engine/Classes/Components/ActorComponent.h>

#include <Runtime/CoreUObject/Public/UObject/WeakInterfacePtr.h>

#include "InteractionComponent.generated.h"

class IHoverableInterface;
class IPlayerViewInterface;

UCLASS(MinimalAPI)
class UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UInteractionComponent(const FObjectInitializer& InObjectInitialiser);

#if WITH_CLIENT_CODE
	void BeginPlay() override;
	void SetupComponentInputBindings(UInputComponent& PlayerInputComponent) override;
#endif //WITH_CLIENT_CODE

	UPROPERTY(EditDefaultsOnly)
	float TraceDistance;

private:

	void StartUse();
	void EndUse();

	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void UpdateHover(const float InDeltaTime);
	void UpdateUse(const float InDeltaTime);

	void OnTraceComplete(const FTraceHandle& InHandle, FTraceDatum& InData);
	void ProcessData(const FTraceDatum& InTraceData);
	void ProcessHit(const FHitResult& InResult);

	void SetNewHover(IHoverableInterface& InNewHover);
	void ClearCurrentHover();

	bool IsHoveringDifferentItem(const IHoverableInterface& InHoverable) const;
	FCollisionQueryParams TraceParams;
	FTraceHandle TraceHandle;
	FTraceDelegate TraceDelegate;

	bool CanTrace;
	
	TWeakInterfacePtr<IPlayerViewInterface> CachedViewInterface;
	TWeakInterfacePtr<IHoverableInterface> CurrentHover;

	bool IsUsing;
	float UseTime;
	float TapLength;
};