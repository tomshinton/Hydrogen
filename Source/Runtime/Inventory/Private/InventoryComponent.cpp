#include "Runtime/Inventory/Public/InventoryComponent.h"
#include "Runtime/Inventory/Public/InventorySettings.h"

#include "Runtime/Inventory/Public/Helpers/InventoryHelpers.h"

#include <Runtime/Engine/Public/Net/UnrealNetwork.h>

DEFINE_LOG_CATEGORY_STATIC(InventoryComponentLog, Log, Log);

UInventoryComponent::UInventoryComponent()
	: Inventory()
	, ItemsLookup(nullptr)
	, AsyncLoader(new FAsyncLoader())
{
	bReplicates = true;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	if (AsyncLoader.IsValid())
	{
		CacheItemsLookup();
	}
	else
	{
		UE_LOG(InventoryComponentLog, Error, TEXT("Could not load ItemsData table - async loader is invalid"));
	}
}

void UInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UInventoryComponent, Inventory);
}

#if !UE_BUILD_SHIPPING
void UInventoryComponent::PrintPlayerInventory()
{
	const TArray<FItemSlot*> Slots = Inventory.GetFlatInventory();
	for (int32 i = 0; i < Slots.Num(); ++i)
	{
		const FItemSlot* CurrentSlot = Slots[i];
		UE_LOG(InventoryComponentLog, Log, TEXT("[%i] %s (%i)"),
			i + 1,
			CurrentSlot->IsEmpty() ? TEXT("Empty") : *CurrentSlot->Info.GetValue().ItemName.ToString(),
			CurrentSlot->Quantity);
	}
}
#endif //!UE_BUILD_SHIPPING

void UInventoryComponent::InitaliseInventory()
{
	if (GetNetMode() == NM_DedicatedServer)
	{
		Inventory.Initialise();
	}
}

void UInventoryComponent::CacheItemsLookup()
{
	if (const UInventorySettings* InventorySettings = GetDefault<UInventorySettings>())
	{
		AsyncLoader->RequestLoad<const UDataTable>(InventorySettings->ItemsTable, [WeakThis = TWeakObjectPtr<UInventoryComponent>(this)](const UDataTable& InLoadedTable)
		{
			if (UInventoryComponent* StrongThis = WeakThis.Get())
			{
				StrongThis->ItemsLookup = &InLoadedTable;
				StrongThis->InitaliseInventory();
			}
		});
	}
}

void UInventoryComponent::OnRep_Inventory(const FInventory& InLastInventory)
{
	UE_LOG(InventoryComponentLog, Log, TEXT("%s's inventory repped"), *GetOwner()->GetName());
}

void UInventoryComponent::PopulateSlotFromLookup(FItemSlot* InSlot, const FName& InName)
{
	FString Context;
	if (FItemRow* FoundRow = ItemsLookup->FindRow<FItemRow>(InName, Context, true))
	{
		InSlot->ItemName = InName;
		InSlot->Info = *FoundRow;
	}
}

#if WITH_SERVER_CODE
void UInventoryComponent::AddItem(const FName& InItem, const uint8 InAmount)
{
	uint8 AmountLeft = InAmount;

	while (AmountLeft > 0)
	{
		const TArray<FItemSlot*> ViableSlots = Inventory.GetSlotsByPredicate([&InItem](const FItemSlot* Slot)
		{
			if (Slot->IsEmpty())
			{
				return true;
			}
			else if (Slot->ItemName == InItem && !Slot->IsFull())
			{
				return true;
			}
			
			return false;

			return (Slot->ItemName == InItem && !Slot->IsFull()) || Slot->IsEmpty();
		});

		if (ViableSlots.Num() > 0)
		{
			UE_LOG(InventoryComponentLog, Log, TEXT("Found %i viable slots - attempting to add %i"), ViableSlots.Num(), AmountLeft);
			if (FItemSlot* TargetSlot = ViableSlots[0])
			{
				if (TargetSlot->IsEmpty())
				{
					PopulateSlotFromLookup(TargetSlot, InItem);
				}

				//Passed in by ref
				TargetSlot->TryAddTo(AmountLeft);
			}
		}
		else
		{
			break;
		}
	}

	PrintPlayerInventory();
}
#endif //WITH_SERVER_CODE

#if WITH_SERVER_CODE
void UInventoryComponent::RemoveItem(const FName& InItem, const uint8 InAmount)
{
	int8 AmountLeft = InAmount;

	while (AmountLeft > 0)
	{
		const TArray<FItemSlot*> ViableSlots = Inventory.GetSlotsByPredicate([&InItem](const FItemSlot* Slot)
		{
			return Slot->ItemName == InItem && !Slot->IsEmpty();
		});

		//Doing this backwards gives us a more aesthetic experience
		if (ViableSlots.Num() > 0)
		{
			if (FItemSlot* TargetSlot = ViableSlots.Last())
			{
				TargetSlot->TryRemoveFrom(AmountLeft);
			}
		}
		else
		{
			break;
		}
	}

	PrintPlayerInventory();
}
#endif //WITH_SERVER_CODE
