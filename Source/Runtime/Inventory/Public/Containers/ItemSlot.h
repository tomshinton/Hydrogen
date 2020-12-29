#pragma once

#include "Runtime/Inventory/Public/Containers/ContainerBase.h"

#include "Runtime/Items/Public/ItemRow.h"

#include "ItemSlot.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemSlotChanged, uint8 /*Quantity from*/, uint8 /*Quantity To*/)

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

	FOnItemSlotChanged OnSlotChanged;

	void TryAddTo(uint8& InAmountToAdd);
	void TryRemoveFrom(int8& InAmountToRemove);

	void ClearSlot();
	bool IsEmpty() const;
	bool IsFull() const;
	bool CanStoreItem(const FName& InName) const;

	bool operator==(const FItemSlot& InOtherInfo) const;

};