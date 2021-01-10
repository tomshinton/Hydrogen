// Hydrogen 2020

#pragma once

#include <Runtime/Core/Public/CoreMinimal.h>
#include <Runtime/Engine/Classes/GameFramework/Character.h>

#include <Runtime/Camera/Public/PlayerViewInterface.h>

#include "HydrogenPlayerCharacter.generated.h"

class UInteractionComponent;
class UPlayerCameraComponent;

UCLASS(MinimalAPI)
class AHydrogenPlayerCharacter : public ACharacter
	, public IPlayerViewInterface
{
	GENERATED_BODY()

public:

	AHydrogenPlayerCharacter(const FObjectInitializer& InObjectInitialiser);

	//IPlayerViewInterface
	virtual FTransform GetCameraTransform() const override final;
	//~IPlayerViewInterface

protected:

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	UPlayerCameraComponent* PlayerCamera;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	UInteractionComponent* InteractionComponent;
};
