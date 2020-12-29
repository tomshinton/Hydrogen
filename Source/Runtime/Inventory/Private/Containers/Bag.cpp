#include "Runtime/Inventory/Public/Containers/Bag.h"

FBag::FBag()
	: FContainerBase()
	, SlotCount(0)
	, Filters()
	, Slots()
{

}

FBag::FBag(const FBag& InSourceBag)
	: FContainerBase()
	, SlotCount(InSourceBag.SlotCount)
	, Filters(InSourceBag.Filters)
	, Slots(InSourceBag.Slots)
{
	if (InSourceBag.Slots.Num() == 0)
	{
		Initialise(SlotCount);
	}
	else
	{
		ContainerID = InSourceBag.ContainerID;
	}
}

void FBag::Initialise(const uint8 InSlotCount)
{
	if (Slots.Num() == SlotCount)
	{
		//this bag is already initialised - bail out. This can happen when working with testBags in design environments.
		//for instance, the Hotbar and InventoryBags being designed with SyncProps
		return;
	}
	else
	{
		ContainerID = FGuid::NewGuid();
		Slots.Empty();

		SlotCount = InSlotCount;
		Slots.Reserve(SlotCount);

		for (uint8 i = 0; i < SlotCount; ++i)
		{
			FItemSlot NewSlot = FItemSlot();
			NewSlot.ContainerID = FGuid::NewGuid();

			Slots.Emplace(NewSlot);
		}
	}
}

TArray<const FItemSlot*> FBag::GetSlots() const
{
	TArray<const FItemSlot*> SlotPtrs;

	for (const FItemSlot& Slot : Slots)
	{
		SlotPtrs.Add(&Slot);
	}

	return SlotPtrs;
}

