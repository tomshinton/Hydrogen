#pragma once

#include "Runtime/Inventory/Public/Containers/ContainerBase.h"

#include "Runtime/Items/Public/ItemRow.h"

#include "ItemSlot.generated.h"

USTRUCT()
struct FItemSlot : public FContainerBase
{
	GENERATED_BODY()

public:

	FItemSlot();

	TOptional<FItemRow> Info;

	UPROPERTY()
	FName ItemName;

	UPROPERTY()
	uint8 Quantity;

	void TryAddTo(uint8& InAmountToAdd);
	void TryRemoveFrom(int8& InAmountToRemove);

	void ClearSlot();
	bool IsEmpty() const;
	bool IsFull() const;
	bool CanStoreItem(const FName& InName) const;
};