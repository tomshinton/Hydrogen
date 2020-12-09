// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Runtime/Core/Public/CoreMinimal.h>
#include <Runtime/Engine/Classes/GameFramework/GameModeBase.h>

#include "HydrogenGameModeBase.generated.h"

UCLASS(MinimalAPI)
class AHydrogenGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	AHydrogenGameModeBase(const FObjectInitializer& InObjectInitialiser);
};
