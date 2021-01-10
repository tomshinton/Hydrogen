#include "UI/UICore/Public/HydrogenHUD.h"
#include "SharedPointer.h"

AHydrogenHUD::AHydrogenHUD(const FObjectInitializer& InObjectInitialiser)
	: UIPoolProvider(*this)
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bAllowTickOnDedicatedServer = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

DEFINE_LOG_CATEGORY_STATIC(HydrogenHudLog, Log, Log)

#if WITH_CLIENT_CODE
void AHydrogenHUD::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(HydrogenHudLog, Log, TEXT("Preheating UIPool"));
	UIPoolProvider.InitialisePreheat(UIPoolSeeds);
}
#endif //WITH_CLIENT_CODE


