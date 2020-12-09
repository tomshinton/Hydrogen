#include "Hydrogen/Public/HydrogenGameModeBase.h"

#include "Hydrogen/Public/HydrogenPlayerController.h"
#include "Hydrogen/Public/HydrogenPlayerCharacter.h"

AHydrogenGameModeBase::AHydrogenGameModeBase(const FObjectInitializer& InObjectInitialiser)
	: Super(InObjectInitialiser)
{
	DefaultPawnClass = AHydrogenPlayerCharacter::StaticClass();
	PlayerControllerClass = AHydrogenPlayerController::StaticClass();
}

