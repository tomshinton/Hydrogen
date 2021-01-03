#include "Runtime/Inventory/Public/InventoryComponent.h"
#include "Runtime/Inventory/Public/InventorySettings.h"

#include "Runtime/Inventory/Public/Helpers/InventoryHelpers.h"

#include <Runtime/Engine/Public/Net/UnrealNetwork.h>

DEFINE_LOG_CATEGORY_STATIC(InventoryComponentLog, Log, Log);

UInventoryComponent::UInventoryComponent()
	: Inventory()
	, ItemsLookup(nullptr)
	, AsyncLoader(new FAsyncLoader())
	, OnInventoryUpdated()
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
	UE_LOG(InventoryComponentLog, Log, TEXT("Inventory ID: %s"), *Inventory.ContainerID.ToString());

	const TArray<const FItemSlot*> Slots = Inventory.GetFlatInventory();
	for (int32 i = 0; i < Slots.Num(); ++i)
	{
		const FItemSlot* CurrentSlot = Slots[i];
		UE_LOG(InventoryComponentLog, Log, TEXT("%s [%i] %s (%i) ID: %s"),
			GetNetMode() == NM_DedicatedServer ? TEXT("Server") : TEXT("Client"),
			i + 1,
			CurrentSlot->IsEmpty() ? TEXT("Empty") : *CurrentSlot->Info.GetValue().ItemName.ToString(),
			CurrentSlot->Quantity,
			*CurrentSlot->ContainerID.ToString());
	}
}
#endif //!UE_BUILD_SHIPPING

FOnInventoryReceived& UInventoryComponent::GetOnInventoryReceived()
{
	return OnInventoryReceived;
}

FOnInventoryUpdated& UInventoryComponent::GetOnInventoryUpdated()
{
	return OnInventoryUpdated;
}

const FInventory* UInventoryComponent::GetInventory() const
{
	return &Inventory;
}

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

				if (StrongThis->GetNetMode() == NM_DedicatedServer)
				{
					StrongThis->InitaliseInventory();
				}
			}
		});
	}
}

void UInventoryComponent::OnRep_Inventory(const FInventory& InLastInventory)
{
#if WITH_CLIENT_CODE
	if (GetNetMode() != NM_DedicatedServer)
	{
		UE_LOG(InventoryComponentLog, Log, TEXT("%s's inventory repped"), *GetOwner()->GetName());
		OnInventoryUpdated.Broadcast(&Inventory);

		if (!Inventory.IsInitialised)
		{
			Inventory.IsInitialised = true;
			OnInventoryReceived.Broadcast();
		}

		UpdateChangedSlots(InLastInventory);
	}
#endif //WITH_CLIENT_CODE
}

#if WITH_CLIENT_CODE
void UInventoryComponent::UpdateChangedSlots(const FInventory& InLastInventory) const
{
	const TArray<const FItemSlot*> ChangedSlots = InventoryHelpers::GetAlteredSlots(Inventory, InLastInventory);
	for (const FItemSlot* Slot : ChangedSlots)
	{
		const FItemSlot LastState = *Slot;

		if (ItemsLookup != nullptr)
		{
			FItemSlot* SlotMutable = const_cast<FItemSlot*>(Slot);
			if (Slot->IsEmpty() && Slot->Quantity > 0)
			{
				PopulateSlotFromLookup(SlotMutable, Slot->ItemName);
			}
			else if(!Slot->IsEmpty() && Slot->Quantity <= 0)
			{
				SlotMutable->ClearSlot();
			}
		}

		Slot->OnSlotChanged.Broadcast(LastState);
	}
}
#endif //WITH_CLIENT_CODE

void UInventoryComponent::PopulateSlotFromLookup(FItemSlot* InSlot, const FName& InName) const
{
	if (InName.IsNone())
	{
		return;
	}
	else
	{
		InSlot->ItemName = InName;

		FString Context;
		if (FItemRow* FoundRow = ItemsLookup->FindRow<FItemRow>(InName, Context, true))
		{
			InSlot->Info = *FoundRow;
		}
	}
}

#if WITH_SERVER_CODE
void UInventoryComponent::AddItem(const FName& InItem, const uint8 InAmount)
{
	uint8 AmountLeft = InAmount;

	while (AmountLeft > 0)
	{
		const TArray<const FItemSlot*> ViableSlots = Inventory.GetSlotsByPredicate([&InItem](const FItemSlot* Slot)
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
			if (const FItemSlot* TargetSlot = ViableSlots[0])
			{
				FItemSlot* SlotMutable = const_cast<FItemSlot*>(TargetSlot);
				if (TargetSlot->IsEmpty())
				{
					PopulateSlotFromLookup(SlotMutable, InItem);
				}

				//Passed in by ref
				SlotMutable->TryAddTo(AmountLeft);
			}
		}
		else
		{
			break;
		}
	}

	OnInventoryUpdated.Broadcast(&Inventory);
}
#endif //WITH_SERVER_CODE

#if WITH_SERVER_CODE
void UInventoryComponent::RemoveItem(const FName& InItem, const uint8 InAmount)
{
	int8 AmountLeft = InAmount;

	while (AmountLeft > 0)
	{
		const TArray<const FItemSlot*> ViableSlots = Inventory.GetSlotsByPredicate([&InItem](const FItemSlot* Slot)
		{
			return Slot->ItemName == InItem && !Slot->IsEmpty();
		});

		//Doing this backwards gives us a more aesthetic experience
		if (ViableSlots.Num() > 0)
		{
			if (const FItemSlot* TargetSlot = ViableSlots.Last())
			{
				FItemSlot* SlotMutable = const_cast<FItemSlot*>(TargetSlot);
				SlotMutable->TryRemoveFrom(AmountLeft);
			}
		}
		else
		{
			break;
		}
	}

	OnInventoryUpdated.Broadcast(&Inventory);
}
#endif //WITH_SERVER_CODE
