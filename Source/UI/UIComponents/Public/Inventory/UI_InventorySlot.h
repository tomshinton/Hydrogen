#pragma once

#include <Runtime/UMG/Public/Blueprint/UserWidget.h>

#include <Runtime/CoreUObject/Public/UObject/WeakInterfacePtr.h>
#include <Runtime/Inventory/Public/InventoryInterface.h>

#include "UI_InventorySlot.generated.h"

class UImage;
class UTextBlock;
struct FItemSlot;

UCLASS(MinimalAPI, Blueprintable, abstract)
class UUI_InventorySlot : public UUserWidget
{
	GENERATED_BODY()

public:

	UUI_InventorySlot(const FObjectInitializer& InObjectInitialiser);

	UPROPERTY(meta=(BindWidget))
	UTextBlock* QuantityText;

	UPROPERTY(meta = (BindWidget))
	UImage* ItemImage;

	void SetAssociatedSlot(IInventoryInterface* InSourceInventory, const FGuid& InAssociatedSlotID);

private:

	void NativeConstruct() override;
	void BindToSlot();
	
	void SetQuantityText(const FItemSlot* InSourceSlot);
	void SetItemImage(const FItemSlot* InSourceSlot);

	TWeakInterfacePtr<IInventoryInterface> SourceInventoryInterface;
	FGuid AssociatedSlotID;
};
