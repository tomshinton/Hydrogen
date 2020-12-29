// Hydrogen 2020

#pragma once

#include <Runtime/UMG/Public/Blueprint/UserWidget.h>

#include <Runtime/Inventory/Public/Containers/Bag.h>

#include "UI_Hotbar.generated.h"

class IInventoryInterface;
class UUI_InventorySlot;
class UVerticalBox;

UCLASS(MinimalAPI)
class UUI_Hotbar : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UUI_Hotbar(const FObjectInitializer& InObjectInitialiser);

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere)
	TArray<FBag> TestBags;
#endif //WITH_EDITORONLY_DATA

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUI_InventorySlot> InventorySlotClass;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* HotbarBox;

private:

	void SynchronizeProperties() override;
	void NativeConstruct() override;

	void SourceBags();
	void AddBar(IInventoryInterface* InSourceInventory, const FBag* InSourceBag);
};
