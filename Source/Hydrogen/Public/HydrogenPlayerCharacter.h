// Hydrogen 2020

#pragma once

#include <Runtime/Core/Public/CoreMinimal.h>
#include <Runtime/Engine/Classes/GameFramework/Character.h>

#include "HydrogenPlayerCharacter.generated.h"

UCLASS()
class AHydrogenPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AHydrogenPlayerCharacter(const FObjectInitializer& InObjectInitialiser);
};
