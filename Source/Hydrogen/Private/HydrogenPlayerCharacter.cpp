// Hydrogen 2020

#include "Hydrogen/Public/HydrogenPlayerCharacter.h"

#include <Runtime/Camera/Public/PlayerCameraComponent.h>
#include <Runtime/Interaction/Public/InteractionComponent.h>
#include <Runtime/Movement/Public/HydrogenMovementComponent.h>

namespace HydrogenPlayerCharacterPrivate
{
	const FName PlayerCameraName = TEXT("PlayerCamera");
	const FName InteractionComponentName = TEXT("InteractionComponent");
}

AHydrogenPlayerCharacter::AHydrogenPlayerCharacter(const FObjectInitializer& InObjectInitialiser)
	: Super(InObjectInitialiser.SetDefaultSubobjectClass<UHydrogenMovementComponent>(ACharacter::CharacterMovementComponentName))
	, PlayerCamera(InObjectInitialiser.CreateDefaultSubobject<UPlayerCameraComponent>(this, HydrogenPlayerCharacterPrivate::PlayerCameraName))
	, InteractionComponent(InObjectInitialiser.CreateDefaultSubobject<UInteractionComponent>(this, HydrogenPlayerCharacterPrivate::InteractionComponentName))
{
	PlayerCamera->SetupAttachment(RootComponent);
}

#if WITH_CLIENT_CODE
FTransform AHydrogenPlayerCharacter::GetCameraTransform() const
{
	if (PlayerCamera != nullptr)
	{
		return PlayerCamera->GetComponentTransform();
	}

	return FTransform::Identity;
}
#endif //WITH_CLIENT_CODE
