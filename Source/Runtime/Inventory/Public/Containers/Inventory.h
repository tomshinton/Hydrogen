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

	UPROPERTY(EditAnywhere, Category = "Defaults", NotReplicated)
	TArray<FBag> InitialBags;

private:

	UPROPERTY()
	TArray<FBag> Bags;
};