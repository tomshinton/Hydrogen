#pragma once

#include "OverlayPair.generated.h"

class UUI_Overlay;

USTRUCT()
struct FOverlayPair
{
	GENERATED_BODY()

public:

	FOverlayPair()
		: Binding()
		, OverlayClass(nullptr)
		, Overlay(nullptr)
	{};

	UPROPERTY(EditAnywhere)
	FName Binding;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUI_Overlay> OverlayClass;

	UPROPERTY()
	UUI_Overlay* Overlay;
};