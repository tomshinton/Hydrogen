#pragma once

#include "Runtime/Inventory/Public/Containers/ContainerBase.h"
#include "Runtime/Inventory/Public/Containers/Bag.h"


#include "Inventory.generated.h"

USTRUCT()
struct FInventory : public FContainerBase
{
	GENERATED_BODY()

public:

	FInventory();
	
	void Initialise();
	TArray<FItemSlot*> GetFlatInventory();

	UPROPERTY(EditAnywhere, Category = "Defaults", NotReplicated)
	TArray<FBag> InitialBags;

	TArray<FItemSlot*> GetSlotsByPredicate(const TFunction<bool(const FItemSlot* Slot)>& InPredicate);

private:

	UPROPERTY()
	TArray<FBag> Bags;
};