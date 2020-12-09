// Hydrogen 2020

#include "Hydrogen/Public/HydrogenCheatManager.h"

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
