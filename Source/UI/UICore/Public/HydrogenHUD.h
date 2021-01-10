#pragma once

#include <Runtime/Core/Public/CoreMinimal.h>
#include <Runtime/CoreUObject/Public/UObject/ObjectMacros.h>
#include <Runtime/Engine/Classes/GameFramework/HUD.h>

#include <UI/UIPooling/Public/UIPoolProvider.h>
#include <UI/UIPooling/Public/UIPoolProviderInterface.h>
#include <UI/UIPooling/Public/UIPoolSeed.h>

#include "HydrogenHUD.generated.h"

UCLASS()
class AHydrogenHUD : public AHUD
	, public IUIPoolProviderInterface
{
	GENERATED_BODY()

public:

	AHydrogenHUD(const FObjectInitializer& InObjectInitialiser);

	//AActor
#if WITH_CLIENT_CODE
	virtual void BeginPlay() override;
#endif //WITH_CLIENT_CODE
	//~AActor

	//IUIPoolProviderInterface
	virtual FUIPoolProvider& GetPoolProvider() override final { return UIPoolProvider; }
	//~IUIPoolProviderInterface

protected:

	UPROPERTY(EditDefaultsOnly)
	TArray<FUIPoolSeed> UIPoolSeeds;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> TestUIClass;

private:

#if WITH_CLIENT_CODE
	FUIPoolProvider UIPoolProvider;
#endif //WITH_CLIENT_CODE
};