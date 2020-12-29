#include "Runtime/Inventory/Public/Containers/Inventory.h"

FInventory::FInventory()
	: FContainerBase()
	, InitialBags()
	, IsInitialised(false)
	, Bags()
{

}

#if WITH_SERVER_CODE
void FInventory::Initialise()
{
	ContainerID = FGuid::NewGuid();

	Bags.Reserve(InitialBags.Num());

	for (const FBag& Bag : InitialBags)
	{
		Bags.Emplace(FBag(Bag));
	}

	IsInitialised = true;
}
#endif //WITH_SERVER_CODE

TArray<const FItemSlot*> FInventory::GetFlatInventory() const
{
	QUICK_SCOPE_CYCLE_COUNTER(STAT_Inventory_GetFlatInventory);

	TArray<const FItemSlot*> Slots;

	for (const FBag& Bag : Bags)
	{
		Slots.Append(Bag.GetSlots());
	}

	return Slots;
}

TArray<const FItemSlot*> FInventory::GetSlotsByPredicate(const TFunction<bool(const FItemSlot* Slot)>& InPredicate) const
{
	QUICK_SCOPE_CYCLE_COUNTER(STAT_Inventory_GetSlotByPredicate);

	return GetFlatInventory().FilterByPredicate(InPredicate);
}

TArray<const FBag*> FInventory::GetBagsByPredicate(const TFunction<bool(const FBag* Bag)>& InPredicate) const
{
	TArray<const FBag*> BagPtrs;
	for (const FBag& Bag : Bags)
	{
		BagPtrs.Add(&Bag);
	}

	return BagPtrs.FilterByPredicate(InPredicate);
}

