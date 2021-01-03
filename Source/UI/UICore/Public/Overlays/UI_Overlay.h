#pragma once

#include <Runtime/UMG/Public/Blueprint/UserWidget.h>


#include "UI_Overlay.generated.h"

UCLASS()
class UUI_Overlay : public UUserWidget
{
	GENERATED_BODY()

public:

	UUI_Overlay(const FObjectInitializer& InObjectInitialiser);
	virtual void OnSummon();
};