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

