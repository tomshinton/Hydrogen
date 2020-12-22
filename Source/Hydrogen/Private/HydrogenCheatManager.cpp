// Hydrogen 2020

#include "Hydrogen/Public/HydrogenCheatManager.h"

#include <Runtime/Inventory/Public/InventoryInterface.h>

DEFINE_LOG_CATEGORY_STATIC(HydrogenCheatManagerLog, Log, Log)

void UHydrogenCheatManager::TestNetworkedLog(const FString& InTestLog)
{
	if (GetOwningController()->GetNetMode() == NM_DedicatedServer)
	{
		UE_LOG(HydrogenCheatManagerLog, Log, TEXT("%s"), *InTestLog);
	}
	else
	{
		EoS("TestNetworkedLog " + InTestLog);
	}
}

void UHydrogenCheatManager::AddItemToPlayer(const FName& InName, const uint8 InAmount)
{
	if (APlayerController* LocalController = GetOwningController())
	{
		if (LocalController->GetNetMode() == NM_DedicatedServer)
		{
			if (IInventoryInterface* InventoryInterface = LocalController->GetInterface<IInventoryInterface>())
			{
				InventoryInterface->AddItem(InName, InAmount);
			}
		}
		else
		{
			EoS("AddItemToPlayer " + InName.ToString() + " " + FString::FromInt(InAmount));
		}
	}
}

void UHydrogenCheatManager::RemoveItemFromPlayer(const FName& InName, const uint8 InAmount)
{
	if (APlayerController* LocalController = GetOwningController())
	{
		if (LocalController->GetNetMode() == NM_DedicatedServer)
		{
			if (IInventoryInterface* InventoryInterface = LocalController->GetInterface<IInventoryInterface>())
			{
				InventoryInterface->RemoveItem(InName, InAmount);
			}
		}
		else
		{
			EoS("RemoveItemFromPlayer " + InName.ToString() + " " + FString::FromInt(InAmount));
		}
	}
}

void UHydrogenCheatManager::PrintPlayerInventory()
{
	if (APlayerController* LocalController = GetOwningController())
	{
		if (LocalController->GetNetMode() == NM_DedicatedServer)
		{
			if (IInventoryInterface* InventoryInterface = LocalController->GetInterface<IInventoryInterface>())
			{
				InventoryInterface->PrintPlayerInventory();
			}
		}
		else
		{
			EoS("PrintPlayerInventory");
		}
	}
}
