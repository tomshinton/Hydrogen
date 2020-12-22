#pragma once

#include <Runtime/Core/Public/CoreMinimal.h>
#include <Runtime/CoreUObject/Public/UObject/ObjectMacros.h>
#include <Runtime/CoreUObject/Public/Serialization/AsyncLoader.h>

#include <Runtime/Engine/Classes/Components/ActorComponent.h>

#include "Runtime/Inventory/Public/Containers/Inventory.h"
#include "Runtime/Inventory/Public/InventoryInterface.h"

#include "InventoryComponent.generated.h"

class UDataTable;

UCLASS(MinimalAPI)
class UInventoryComponent : public UActorComponent
	, public IInventoryInterface
{
	GENERATED_BODY()

public:

	UInventoryComponent();

	//UObject
	void BeginPlay() override;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	//~UObject

	//IInventoryInterface
#if WITH_SERVER_CODE
	virtual void AddItem(const FName& InItem, const uint8 InAmount) override;
	virtual void RemoveItem(const FName& InItem, const uint8 InAmount) override;
#endif //WITH_SERVER_CODE
#if !UE_BUILD_SHIPPING
	virtual void PrintPlayerInventory() override;
#endif //!UE_BUILD_SHIPPING
	//~IInventroyInterface

	UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_Inventory)
	FInventory Inventory;

	UPROPERTY(Transient)
	const UDataTable* ItemsLookup;

private:

	void InitaliseInventory();
	void CacheItemsLookup();

	UFUNCTION()
	void OnRep_Inventory(const FInventory& InLastInventory);

	void PopulateSlotFromLookup(FItemSlot* InSlot, const FName& InName);

	TUniquePtr<FAsyncLoader> AsyncLoader;
};