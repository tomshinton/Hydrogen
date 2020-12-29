#pragma once

#include <Runtime/UMG/Public/Blueprint/UserWidget.h>

#include <Runtime/CoreUObject/Public/UObject/WeakInterfacePtr.h>
#include <Runtime/Inventory/Public/InventoryInterface.h>

#include "UI_InventorySlot.generated.h"

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

	void SetAssociatedSlot(IInventoryInterface* InSourceInventory, const FGuid& InAssociatedSlotID);

private:

	void NativeConstruct() override;
	void BindToSlot();
	
	TWeakInterfacePtr<IInventoryInterface> SourceInventoryInterface;
	FGuid AssociatedSlotID;
};
