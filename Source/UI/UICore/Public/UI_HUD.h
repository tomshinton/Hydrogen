#pragma once

#include <Runtime/UMG/Public/Blueprint/UserWidget.h>

#include "UI_HUD.generated.h"

UCLASS(MinimalAPI, Blueprintable, abstract)
class UUI_HUD : public UUserWidget
{
	GENERATED_BODY()

public:

	UUI_HUD(const FObjectInitializer& InObjectInitialiser);
};
