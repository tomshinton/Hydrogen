#include "UI/UIComponents/Public/Inventory/UI_InventorySlot.h"

#include <Runtime/Inventory/Public/Containers/Inventory.h>
#include <Runtime/Inventory/Public/Containers/ItemSlot.h>
#include <Runtime/Inventory/Public/InventoryInterface.h>

#include <Runtime/UMG/Public/Components/Image.h>
#include <Runtime/UMG/Public/Components/TextBlock.h>

UUI_InventorySlot::UUI_InventorySlot(const FObjectInitializer& InObjectInitialiser)
	: Super(InObjectInitialiser)
	, QuantityText(nullptr)
	, AssociatedSlotID()
{

}

void UUI_InventorySlot::NativeConstruct()
{
	Super::NativeConstruct();

	if (AssociatedSlotID.IsValid())
	{
		BindToSlot();
	}
}

void UUI_InventorySlot::SetAssociatedSlot(IInventoryInterface* InSourceInventory, const FGuid& InAssociatedSlotID)
{
	if (InSourceInventory != nullptr)
	{
		SourceInventoryInterface = TWeakInterfacePtr<IInventoryInterface>(*InSourceInventory);
	}

	AssociatedSlotID = InAssociatedSlotID;
}

void UUI_InventorySlot::BindToSlot()
{
	const TArray<const FItemSlot*> SourceSlot = SourceInventoryInterface->GetInventory()->GetSlotsByPredicate([AssociatedSlotID = AssociatedSlotID](const FItemSlot* CurrentSlot)
	{
		return CurrentSlot->ContainerID == AssociatedSlotID;
	});

	if (const FItemSlot* FoundSlot = SourceSlot[0])
	{
		FItemSlot* SlotMutable = const_cast<FItemSlot*>(FoundSlot);
		SlotMutable->OnSlotChanged.AddLambda([WeakThis = TWeakObjectPtr<UUI_InventorySlot>(this), FoundSlot = FoundSlot](const FItemSlot& InLastState)
		{
			if (UUI_InventorySlot* StrongThis = WeakThis.Get())
			{
				if (FoundSlot != nullptr)
				{
					StrongThis->SetQuantityText(FoundSlot);
					StrongThis->SetItemImage(FoundSlot);
				}
			}
		});

		SetQuantityText(FoundSlot);
		SetItemImage(FoundSlot);
	}
}

void UUI_InventorySlot::SetQuantityText(const FItemSlot* InSourceSlot)
{
	if (QuantityText != nullptr)
	{
		const uint8 InNewQuantity = InSourceSlot->Quantity;

		if (InNewQuantity > 0)
		{
			QuantityText->SetVisibility(ESlateVisibility::Visible);
			QuantityText->SetText(FText::AsNumber(InNewQuantity));
		}
		else
		{
			QuantityText->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UUI_InventorySlot::SetItemImage(const FItemSlot* InSourceSlot)
{
	if (ItemImage != nullptr)
	{
		if (InSourceSlot->IsEmpty())
		{
			ItemImage->SetVisibility(ESlateVisibility::Hidden);
		}
		else if (InSourceSlot->Info.IsSet())
		{
			ItemImage->SetVisibility(ESlateVisibility::Visible);
			const FItemRow Info = InSourceSlot->Info.GetValue();
			ItemImage->SetBrushFromTexture(Info.ItemIcon);
		}
	}
}
