// Hydrogen 2020

#include "UI/UIComponents/Public/Inventory/UI_Hotbar.h"
#include "UI/UIComponents/Public/Inventory/UI_InventorySlot.h"

#include <Runtime/Inventory/Public/Containers/Bag.h>
#include <Runtime/Inventory/Public/Containers/BagFilters.h>
#include <Runtime/Inventory/Public/Containers/Inventory.h>
#include <Runtime/Inventory/Public/InventoryInterface.h>
#include <Runtime/UMG/Public/Blueprint/WidgetTree.h>
#include <Runtime/UMG/Public/Components/HorizontalBox.h>
#include <Runtime/UMG/Public/Components/VerticalBox.h>

DEFINE_LOG_CATEGORY_STATIC(HotbarLog, Log, Log)

UUI_Hotbar::UUI_Hotbar(const FObjectInitializer& InObjectInitialiser)
	: Super(InObjectInitialiser)
#if WITH_EDITORONLY_DATA
	, TestBags()
#endif //WITH_EDITORONLY_DATA
	, InventorySlotClass(nullptr)
	, HotbarBox(nullptr)
{

}

void UUI_Hotbar::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	HotbarBox->ClearChildren();

	if (IsDesignTime())
	{
		for (FBag& Bag : TestBags)
		{
			Bag.Initialise(Bag.SlotCount);
			AddBar(nullptr, &Bag);
		}
	}
}

void UUI_Hotbar::NativeConstruct()
{
	Super::NativeConstruct();

	SourceBags();
}

void UUI_Hotbar::SourceBags()
{
	if (HotbarBox != nullptr)
	{
		HotbarBox->ClearChildren();
		if (AActor* LocalController = GetOwningPlayer<AActor>())
		{
			if (IInventoryInterface* LocalInventoryInterface = LocalController->GetInterface<IInventoryInterface>())
			{
				if (const FInventory* Inventory = LocalInventoryInterface->GetInventory())
				{
					const TArray<const FBag*> HotbarBags = Inventory->GetBagsByPredicate([](const FBag* Bag) -> bool
					{
						return Bag->Filters.Contains(UHotbarBagFilter::StaticClass());
					});

					if (HotbarBags.Num() > 0)
					{
						for (const FBag* Bag : HotbarBags)
						{
							AddBar(LocalInventoryInterface, Bag);
						}
					}
					else
					{
						UE_LOG(HotbarLog, Error, TEXT("Local inventory contains no bars with a Hotbar filter applied - cannot build hotbar"));
					}
				}
			}
		}
	}
}

void UUI_Hotbar::AddBar(IInventoryInterface* InSourceInventory, const FBag* InSourceBag)
{
	if (InSourceBag == nullptr)
	{
		UE_LOG(HotbarLog, Error, TEXT("Cannot add bar - source bag ptr is null"));
		return;
	}

	if (InventorySlotClass == nullptr)
	{
		UE_LOG(HotbarLog, Error, TEXT("Cannot add bar - InventorySlotClass is null"));
		return;
	}

	if (HotbarBox != nullptr)
	{
		if (UHorizontalBox* NewBox = NewObject<UHorizontalBox>(this))
		{
			const TArray<const FItemSlot*> Slots = InSourceBag->GetSlots();

			if (Slots.Num() > 0)
			{
				for (const FItemSlot* CurrSlot : Slots)
				{
					if (UUI_InventorySlot* NewSlot = NewObject<UUI_InventorySlot>(NewBox, InventorySlotClass))
					{
						NewSlot->SetAssociatedSlot(InSourceInventory, CurrSlot->ContainerID);
						NewBox->AddChild(NewSlot);
					}
				}

				HotbarBox->AddChild(NewBox);
			}
		}
	}
	else
	{
		UE_LOG(HotbarLog, Error, TEXT("Cannot add bar - HotbarBox is null"));
	}
}
