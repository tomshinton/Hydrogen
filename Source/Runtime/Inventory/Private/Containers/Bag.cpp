#include "Runtime/Inventory/Public/Containers/Bag.h"

FBag::FBag()
	: FContainerBase()
{

}

void FBag::Initialise(const uint8 InSlotCount)
{
	SlotCount = InSlotCount;

	Slots.Reserve(SlotCount);

	for (uint8 i = 0; i < SlotCount; ++i)
	{
		Slots.Emplace(FItemSlot());
	}
}

