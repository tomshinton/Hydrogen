#pragma once

#include <Runtime/Core/Public/CoreMinimal.h>
#include <Runtime/CoreUObject/Public/UObject/ObjectMacros.h>

#include <Runtime/Engine/Classes/Components/ActorComponent.h>

#include "Runtime/Inventory/Public/Containers/Inventory.h"

#include "InventoryComponent.generated.h"

UCLASS(MinimalAPI)
class UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UInventoryComponent();

	//UObject
	void BeginPlay() override;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	//~UObject

	UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_Inventory)
	FInventory Inventory;

private:

	void InitaliseInventory();

	UFUNCTION()
	void OnRep_Inventory(const FInventory& InLastInventory);
};