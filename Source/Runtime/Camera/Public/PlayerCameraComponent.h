#pragma once

#include <Runtime/Core/Public/CoreMinimal.h>
#include <Runtime/CoreUObject/Public/UObject/ObjectMacros.h>

#include <Runtime/Engine/Classes/Camera/CameraComponent.h>

#include "PlayerCameraComponent.generated.h"

UCLASS(MinimalAPI)
class UPlayerCameraComponent : public UCameraComponent
{
	GENERATED_BODY()

public:

	UPlayerCameraComponent(const FObjectInitializer& InObjectInitialiser);

#if WITH_CLIENT_CODE
	void SetupComponentInputBindings(UInputComponent& PlayerInputComponent) override;
#endif //WITH_CLIENT_CODE

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float MoveSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float MaxPitch;

private:

	void LookUp(const float InStrength);
};
