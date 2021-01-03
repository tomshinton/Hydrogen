#pragma once

#include "UI/UICore/Public/Overlays/UI_Overlay.h"

#include "OverlayEvents.generated.h"

USTRUCT()
struct FRequestOverlay
{
	GENERATED_BODY()
	
public:

	FRequestOverlay()
		: Overlay(nullptr)
	{};

	FRequestOverlay(UUI_Overlay& InOverlay)
		: Overlay(&InOverlay)
	{};

	FRequestOverlay(const TSubclassOf<UUI_Overlay>& InOverlayClass, UObject& InOwner)
		: Overlay(NewObject<UUI_Overlay>(&InOwner, InOverlayClass))
	{};

	UPROPERTY()
	UUI_Overlay* Overlay;
};