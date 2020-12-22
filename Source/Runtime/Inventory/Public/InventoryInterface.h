// Sowing Season - Tom Shinton 2020

#pragma once

#include <Runtime/CoreUObject/Public/UObject/Interface.h>

#include "InventoryInterface.generated.h"

UINTERFACE(MinimalAPI)
class UInventoryInterface : public UInterface 
{
	GENERATED_BODY()
};

class IInventoryInterface
{
	GENERATED_BODY()

public:

#if WITH_SERVER_CODE
	virtual void AddItem(const FName& InItem, const uint8 InAmount) = 0;
	virtual void RemoveItem(const FName& InItem, const uint8 InAmount) = 0;
#endif //WITH_SERVER_CODE

#if !UE_BUILD_SHIPPING
	virtual void PrintPlayerInventory() = 0;
#endif //!UE_BUILD_SHIPPING
};