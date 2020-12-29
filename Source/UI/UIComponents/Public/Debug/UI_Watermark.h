// Hydrogen 2020

#pragma once

#include <Runtime/UMG/Public/Blueprint/UserWidget.h>

#include "UI_Watermark.generated.h"

class UTextBlock;

UCLASS(MinimalAPI)
class UUI_Watermark : public UUserWidget
{
	GENERATED_BODY()

public:

	UUI_Watermark(const FObjectInitializer& InObjectInialiser);

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ProjectNameText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ProjectVersionText;

private:

	void NativeConstruct() override;
};
