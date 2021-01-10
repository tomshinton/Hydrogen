#include "UI/UIComponents/Public/Inventory/UI_BagView.h"
#include "UI/UIComponents/Public/Inventory/UI_InventorySlot.h"

#include <Runtime/Inventory/Public/Containers/Inventory.h>
#include <Runtime/UMG/Public/Components/WrapBox.h>
#include <UI/UIPooling/Public/UIPoolProvider.h>

DEFINE_LOG_CATEGORY_STATIC(BagViewLog, Log, Log)
DECLARE_STATS_GROUP(TEXT("HUD"), STATGROUP_Hud, STATCAT_Advanced);

UUI_BagView::UUI_BagView(const FObjectInitializer& InObjectInitialiser)
	: Super(InObjectInitialiser)
	, SlotsBox(nullptr)
#if WITH_EDITORONLY_DATA
	, TestBag()
#endif //WITH_EDITORONLY_DATA
{

}

void UUI_BagView::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (SlotsBox != nullptr)
	{
		SlotsBox->ClearChildren();
		if (AssociatedInventory.IsValid())
		{
			TArray<const FBag*> SourceBags = AssociatedInventory->GetInventory()->GetBagsByPredicate([AssociatedBagID = AssociatedBagID](const FBag* CurrentBag)
			{
				return CurrentBag->ContainerID == AssociatedBagID;
			});

			if (SourceBags.Num() == 1)
			{
				InitialiseView(&(*AssociatedInventory), SourceBags[0]);
			}
			else
			{
				UE_LOG(BagViewLog, Error, TEXT("Expected to find exactly 1 associated bag from ID - actually found %i"), SourceBags.Num());
			}
		}
	}
}

void UUI_BagView::SynchronizeProperties()
{
	Super::SynchronizeProperties();

#if WITH_EDITORONLY_DATA
	if (IsDesignTime())
	{
		if (SlotsBox != nullptr && SlotClass != nullptr)
		{
			TestBag.Initialise(TestBag.SlotCount);
			SlotsBox->ClearChildren();

			InitialiseView(nullptr, &TestBag);
		}
	}
#endif //WITH_EDITORONLY_DATA
}

void UUI_BagView::SetAssociatedBag(IInventoryInterface* InSourceInventory, const FBag* InSourceBag)
{
	AssociatedInventory = *InSourceInventory;
	AssociatedBagID = InSourceBag->ContainerID;
}

DECLARE_CYCLE_STAT(TEXT("UUI_BagView::InitialiseView"), STAT_InitialiseView, STATGROUP_Hud);
void UUI_BagView::InitialiseView(IInventoryInterface* InSourceInventory, const FBag* InSourceBag)
{
	SCOPE_CYCLE_COUNTER(STAT_InitialiseView);

	for (const FItemSlot* ItemSlot : InSourceBag->GetSlots())
	{
		AddSlot(InSourceInventory, ItemSlot);
	}
}

DECLARE_CYCLE_STAT(TEXT("UUI_BagView::AddSlot"), STAT_AddSlot, STATGROUP_Hud);
void UUI_BagView::AddSlot(IInventoryInterface* InSourceInventory, const FItemSlot* InSlot)
{
	SCOPE_CYCLE_COUNTER(STAT_AddSlot);

	if (UUI_InventorySlot* NewSlot = FUIPoolProvider::NewWidget<UUI_InventorySlot>(*SlotsBox, SlotClass))
	{
		NewSlot->SetAssociatedSlot(InSourceInventory, InSlot->ContainerID);
		SlotsBox->AddChild(NewSlot);
	}
}
