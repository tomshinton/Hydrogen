#pragma once

#include "Runtime/Inventory/Public/Containers/ContainerBase.h"

#include "Runtime/Inventory/Public/Containers/BagFilters.h"
#include "Runtime/Inventory/Public/Containers/ItemSlot.h"

#include "Bag.generated.h"

USTRUCT()
struct FBag : public FContainerBase
{
	GENERATED_BODY()

public:

	INVENTORY_API FBag();
	FBag(const FBag& InSourceBag);

	INVENTORY_API void Initialise(const uint8 InSlotCount);
	INVENTORY_API TArray<const FItemSlot*> GetSlots() const;

	UPROPERTY(EditAnywhere)
	uint8 SlotCount;

	UPROPERTY(EditAnywhere, Category = "Filter")
	TArray<TSubclassOf<UBagFilter>> Filters;

private:

	UPROPERTY()
	TArray<FItemSlot> Slots;
};