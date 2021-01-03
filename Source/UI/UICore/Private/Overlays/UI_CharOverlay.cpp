#include "UI/UICore/Public/Overlays/UI_CharOverlay.h"

#include <Runtime/Inventory/Public/Containers/Bag.h>
#include <Runtime/Inventory/Public/Containers/Inventory.h>
#include <Runtime/Inventory/Public/InventoryInterface.h>
#include <Runtime/UMG/Public/Components/VerticalBox.h>
#include <UI/UIComponents/Public/Inventory/UI_BagView.h>

UUI_CharOverlay::UUI_CharOverlay(const FObjectInitializer& InObjectInitialiser)
	: Super(InObjectInitialiser)
{

}

void UUI_CharOverlay::NativeConstruct()
{
	Super::NativeConstruct();

	if (AllBags != nullptr && BagViewClass != nullptr)
	{
		BuildInventoryPanel();
	}
}

void UUI_CharOverlay::BuildInventoryPanel()
{
	AllBags->ClearChildren();

	if (UWorld* World = GetWorld())
	{
		if (APlayerController* LocalController = World->GetFirstPlayerController())
		{
			if (IInventoryInterface* LocalInventory = LocalController->GetInterface<IInventoryInterface>())
			{
				const TArray<const FBag*> HotbarBags = LocalInventory->GetInventory()->GetBagsByPredicate([](const FBag* CurrentBag) { return CurrentBag->Filters.Contains(UHotbarBagFilter::StaticClass()); });
				const TArray<const FBag*> OtherBags = LocalInventory->GetInventory()->GetBagsByPredicate([](const FBag* CurrentBag) { return !CurrentBag->Filters.Contains(UHotbarBagFilter::StaticClass()); });

				//Add hotbar
				for (const FBag* HotbarBag : HotbarBags)
				{
					AddBagView(LocalInventory, HotbarBag);
					//Add a spacer here, or some kind of visual element letting the player know the rest of the bags are different
				}

				//Add all other bags
				for (const FBag* OtherBag : OtherBags)
				{
					AddBagView(LocalInventory, OtherBag);
				}
			}
		}
	}
}

void UUI_CharOverlay::AddBagView(IInventoryInterface* InSourceInventory, const FBag* InSourceBag)
{
	if (UUI_BagView* NewBagView = NewObject<UUI_BagView>(AllBags, BagViewClass))
	{
		NewBagView->SetAssociatedBag(InSourceInventory, InSourceBag);
		AllBags->AddChild(NewBagView);
	}
}
