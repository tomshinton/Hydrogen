#pragma once

#include <Runtime/Core/Public/CoreMinimal.h>

#include <Runtime/CoreUObject/Public/UObject/ObjectMacros.h>
#include <Runtime/Engine/Classes/GameFramework/PlayerController.h>

#include "HydrogenPlayerController.generated.h"

UCLASS()
class AHydrogenPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	AHydrogenPlayerController(const FObjectInitializer& ObjectInitialiser);
	
private:

	void BeginPlay() override;
};
