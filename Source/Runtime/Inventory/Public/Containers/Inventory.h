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
	
#if WITH_SERVER_CODE
	void Initialise();
#endif //WITH_SERVER_CODE

	TArray<const FItemSlot*> GetFlatInventory() const;
	
	INVENTORY_API TArray<const FItemSlot*> GetSlotsByPredicate(const TFunction<bool(const FItemSlot* Slot)>& InPredicate) const;
	INVENTORY_API TArray<const FBag*> GetBagsByPredicate(const TFunction<bool(const FBag* Bag)>& InPredicate) const;

	UPROPERTY(EditAnywhere, Category = "Defaults", NotReplicated)
	TArray<FBag> InitialBags;

	bool IsInitialised;

private:

	UPROPERTY()
	TArray<FBag> Bags;
};