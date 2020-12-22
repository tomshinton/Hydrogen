#include "Runtime/Inventory/Public/Containers/ItemSlot.h"

FItemSlot::FItemSlot()
	: FContainerBase()
{

}

void FItemSlot::TryAddTo(uint8& InAmountToAdd)
{
	const FItemRow RowInfo = Info.GetValue();
	const uint8 SpaceLeftInSlot = RowInfo.StackSize - Quantity;

	if (SpaceLeftInSlot >= InAmountToAdd)
	{
		Quantity += InAmountToAdd;
		InAmountToAdd = 0;
	}
	else
	{
		Quantity = RowInfo.StackSize;
		InAmountToAdd -= SpaceLeftInSlot;
	}
}

void FItemSlot::TryRemoveFrom(int8& InAmountToRemove)
{
	if (Quantity >= InAmountToRemove)
	{
		const uint8 LastQuantity = Quantity;
		Quantity -= InAmountToRemove;
		InAmountToRemove -= (LastQuantity - Quantity);
	}
	else
	{
		InAmountToRemove -= Quantity;
		Quantity = 0;
	}

	if (Quantity <= 0)
	{
		ClearSlot();
	}
}

void FItemSlot::ClearSlot()
{
	ItemName = "";
	Quantity = 0;
	Info = TOptional<FItemRow>();
}

bool FItemSlot::IsEmpty() const
{
	return !Info.IsSet();
}

bool FItemSlot::IsFull() const
{
	const FItemRow RowInfo = Info.GetValue();
	return Quantity == RowInfo.StackSize;
}

bool FItemSlot::CanStoreItem(const FName& InName) const
{
	return InName != ItemName;
}
