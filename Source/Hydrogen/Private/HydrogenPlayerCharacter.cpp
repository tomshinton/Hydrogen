// Hydrogen 2020

#include "Hydrogen/Public/HydrogenPlayerCharacter.h"

#include <Runtime/Camera/Public/PlayerCameraComponent.h>
#include <Runtime/Movement/Public/HydrogenMovementComponent.h>

namespace HydrogenPlayerCharacterPrivate
{
	const FName PlayerCameraName = TEXT("PlayerCamera");
}

AHydrogenPlayerCharacter::AHydrogenPlayerCharacter(const FObjectInitializer& InObjectInitialiser)
	: Super(InObjectInitialiser.SetDefaultSubobjectClass<UHydrogenMovementComponent>(ACharacter::CharacterMovementComponentName))
	, PlayerCamera(InObjectInitialiser.CreateDefaultSubobject<UPlayerCameraComponent>(this, HydrogenPlayerCharacterPrivate::PlayerCameraName))
{
	PlayerCamera->SetupAttachment(RootComponent);
}
