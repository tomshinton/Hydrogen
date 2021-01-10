#pragma once

#include <Runtime/Core/Public/CoreMinimal.h>
#include <Runtime/CoreUObject/Public/UObject/ObjectMacros.h>

#include <Runtime/UMG/Public/Blueprint/UserWidget.h>

#include "UIPoolSeed.generated.h"

USTRUCT()
struct FUIPoolSeed
{
	GENERATED_BODY()

public:

	FUIPoolSeed()
		: Class(nullptr)
		, NumToPreheat(0)
	{}
	FUIPoolSeed(const TSubclassOf<UUserWidget>& InClass, const uint16 InNumToPreheat)
		: Class(InClass)
		, NumToPreheat(InNumToPreheat)
	{};

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> Class;

	UPROPERTY(EditAnywhere)
	uint16 NumToPreheat;
};
