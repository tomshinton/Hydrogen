// Sowing Season - Tom Shinton 2020

#pragma once

#include <Runtime/Engine/Classes/Components/ActorComponent.h>
#include <Runtime/Interaction/Public/Hovering/HoverableInterface.h>

#include "HoverableComponent.generated.h"

DEFINE_LOG_CATEGORY_STATIC(HoverableComponentLog, Log, Log)

UCLASS(MinimalAPI, Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class UHoverableComponent : public UActorComponent
	, public IHoverableInterface
{
	GENERATED_BODY()

public:

	UHoverableComponent(){};

	//IHoverableInterface
	virtual void OnEndHover() override { UE_LOG(HoverableComponentLog, Log, TEXT("Ending hover of %s"), *GetOwner()->GetName()); }
	virtual void OnStartHover() override { UE_LOG(HoverableComponentLog, Log, TEXT("Starting hover of %s"), *GetOwner()->GetName()); }
	virtual AActor* GetActor() override final { return Cast<AActor>(GetOwner()); }
	//~IHoverableInterface
};
