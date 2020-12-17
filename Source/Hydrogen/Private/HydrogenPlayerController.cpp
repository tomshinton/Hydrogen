#include "Hydrogen/Public/HydrogenPlayerController.h"

#include <Runtime/Inventory/Public/InventoryComponent.h>

#if !UE_BUILD_SHIPPING
#include "Hydrogen/Public/HydrogenCheatManager.h"
#endif //!UE_BUILD_SHIPPING

namespace HydrogenPlayerController
{
	const FName InventoryComponentName = TEXT("InventoryComponent");
}

AHydrogenPlayerController::AHydrogenPlayerController(const FObjectInitializer& ObjectInitialiser)
	: Super(ObjectInitialiser)
	, InventoryComponent(ObjectInitialiser.CreateDefaultSubobject<UInventoryComponent>(this, HydrogenPlayerController::InventoryComponentName))
{
#if !UE_BUILD_SHIPPING
	CheatClass = UHydrogenCheatManager::StaticClass();
#endif //!UE_BUILD_SHIPPING
}

void AHydrogenPlayerController::BeginPlay()
{
	Super::BeginPlay();

#if !UE_BUILD_SHIPPING
	EnableCheats();
#endif //!UE_BUILD_SHIPPING
}
