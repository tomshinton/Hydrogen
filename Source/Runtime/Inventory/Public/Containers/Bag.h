#pragma once

#include "Runtime/Inventory/Public/Containers/ContainerBase.h"
#include "Runtime/Inventory/Public/Containers/ItemSlot.h"

#include "Bag.generated.h"

USTRUCT()
struct FBag : public FContainerBase
{
	GENERATED_BODY()

public:

	FBag();

	void Initialise(const uint8 InSlotCount);

	UPROPERTY(EditAnywhere)
	uint8 SlotCount;

private:

	UPROPERTY()
	TArray<FItemSlot> Slots;
};