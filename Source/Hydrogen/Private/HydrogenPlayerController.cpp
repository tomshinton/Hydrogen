#include "Hydrogen/Public/HydrogenPlayerController.h"

#if !UE_BUILD_SHIPPING
#include "Hydrogen/Public/HydrogenCheatManager.h"
#endif //!UE_BUILD_SHIPPING

AHydrogenPlayerController::AHydrogenPlayerController(const FObjectInitializer& ObjectInitialiser)
	: Super(ObjectInitialiser)
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
