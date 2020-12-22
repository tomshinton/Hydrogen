//AirEngine 2020 - Tom Shinton

#pragma once

#include <Runtime/Engine/Classes/Engine/DeveloperSettings.h>

#include "InventorySettings.generated.h"

class UDataTable;

UCLASS(config = Game, defaultconfig, MinimalAPI)
class UInventorySettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	UInventorySettings()
		: ItemsTable("")
	{};

	UPROPERTY(config, EditDefaultsOnly, Category = "Lookup", meta = (AllowedClasses=DataTable))
	FSoftObjectPath ItemsTable;
};
