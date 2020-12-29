// Sowing Season - Tom Shinton 2020

#pragma once

#include <Runtime/CoreUObject/Public/UObject/Interface.h>

#include "InventoryInterface.generated.h"

struct FInventory;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnInventoryUpdated, const FInventory*)
DECLARE_MULTICAST_DELEGATE(FOnInventoryReceived)

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

	virtual FOnInventoryReceived& GetOnInventoryReceived() = 0;
	virtual FOnInventoryUpdated& GetOnInventoryUpdated() = 0;
	virtual const FInventory* GetInventory() const = 0;

#if !UE_BUILD_SHIPPING
	virtual void PrintPlayerInventory() = 0;
#endif //!UE_BUILD_SHIPPING
};