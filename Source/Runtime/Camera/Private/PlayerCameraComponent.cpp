#include "Runtime/Camera/Public/PlayerCameraComponent.h"

namespace PlayerCameraBindings
{
	const FName LookUpBinding = TEXT("LookUp");
}

UPlayerCameraComponent::UPlayerCameraComponent(const FObjectInitializer& InObjectInitialiser)
	: Super(InObjectInitialiser)
{

}

void UPlayerCameraComponent::SetupComponentInputBindings(UInputComponent& PlayerInputComponent)
{
	Super::SetupComponentInputBindings(PlayerInputComponent);

	PlayerInputComponent.BindAxis(PlayerCameraBindings::LookUpBinding, this, &UPlayerCameraComponent::LookUp);
};

void UPlayerCameraComponent::LookUp(const float InStrength)
{
	if (!FMath::IsNearlyZero(InStrength))
	{
		const FRotator CurrentRot = GetComponentRotation();
		const float CurrentPitch = CurrentRot.Pitch;
		const float TargetPitch = FMath::Clamp(CurrentPitch + (InStrength * MoveSpeed), -MaxPitch, MaxPitch);

		SetWorldRotation(FRotator(TargetPitch, CurrentRot.Yaw, CurrentRot.Roll));;
	}
}

