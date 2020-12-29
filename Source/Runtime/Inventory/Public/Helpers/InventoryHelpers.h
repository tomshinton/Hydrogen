#pragma once

namespace InventoryHelpers
{
	static TArray<const FItemSlot*> GetAlteredSlots(const FInventory& InCurrentInventory, const FInventory& InLastInventory)
	{
		QUICK_SCOPE_CYCLE_COUNTER(STAT_InventoryHelpers_GetAlteredSlots);

		TArray<const FItemSlot*> AlteredSlots;

		const TArray<const FItemSlot*> OldSlots = InLastInventory.GetFlatInventory();
		const TArray<const FItemSlot*> NewSlots = InCurrentInventory.GetFlatInventory();

		if (OldSlots.Num() != NewSlots.Num())
		{
			//If the number has drastically changed, mark the whole thing as altered
			AlteredSlots = NewSlots;
		}
		else
		{
			for (const FItemSlot* NewSlot : NewSlots)
			{
				//Manual loop here - contains would be nice for brevity, but obscures a loop anyway
				const int32 IndexOfExisting = OldSlots.IndexOfByPredicate([NewSlot = NewSlot](const FItemSlot* Slot)
				{
					return *NewSlot == *Slot;	
				});

				if (IndexOfExisting == INDEX_NONE)
				{
					AlteredSlots.AddUnique(NewSlot);
				}
			}
		}

		return AlteredSlots;
	}
}