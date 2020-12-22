#include "Runtime/Inventory/Public/Containers/Inventory.h"

FInventory::FInventory()
	: FContainerBase()
{

}

void FInventory::Initialise()
{
	Bags.Reserve(InitialBags.Num());

	for (const FBag& Bag : InitialBags)
	{
		const uint8 LastAddedBag = Bags.Emplace(FBag());
		Bags[LastAddedBag].Initialise(Bag.SlotCount);
	}
}

TArray<FItemSlot*> FInventory::GetFlatInventory()
{
	QUICK_SCOPE_CYCLE_COUNTER(STAT_Inventory_GetFlatInventory);

	TArray<FItemSlot*> Slots;

	for (FBag& Bag : Bags)
	{
		Slots.Append(Bag.GetSlots());
	}

	return Slots;
}

TArray<FItemSlot*> FInventory::GetSlotsByPredicate(const TFunction<bool(const FItemSlot* Slot)>& InPredicate)
{
	QUICK_SCOPE_CYCLE_COUNTER(STAT_Inventory_GetSlotByPredicate);

	return GetFlatInventory().FilterByPredicate(InPredicate);
}

