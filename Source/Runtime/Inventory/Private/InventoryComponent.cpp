#include "Runtime/Inventory/Public/InventoryComponent.h"

#include <Runtime/Engine/Public/Net/UnrealNetwork.h>

DEFINE_LOG_CATEGORY_STATIC(InventoryComponentLog, Log, Log);

UInventoryComponent::UInventoryComponent()
	: Inventory()
{
	bReplicates = true;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	InitaliseInventory();
}

void UInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(UInventoryComponent, Inventory);
}


void UInventoryComponent::InitaliseInventory()
{
	if (GetNetMode() == NM_DedicatedServer)
	{
		Inventory.Initialise();
	}
}

void UInventoryComponent::OnRep_Inventory(const FInventory& InLastInventory)
{
	UE_LOG(InventoryComponentLog, Log, TEXT("%s's inventory repped"), *GetOwner()->GetName());
}

