// Hydrogen 2020

#pragma once

#include <Runtime/Core/Public/CoreMinimal.h>
#include <Runtime/CoreUObject/Public/UObject/ObjectMacros.h>

#include <Runtime/Engine/Classes/GameFramework/CheatManager.h>

#include "HydrogenCheatManager.generated.h"

UCLASS()
class UHydrogenCheatManager : public UCheatManager
{
	GENERATED_BODY()

public:

	UFUNCTION(Exec, Category = "Test")
	void TestNetworkedLog(const FString& InTestLog);
};
