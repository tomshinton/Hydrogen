#pragma once

#include "BagFilters.generated.h"

UCLASS(abstract, hidedropdown, MinimalAPI)
class UBagFilter : public UObject 
{
	GENERATED_BODY()
};

UCLASS(BlueprintType, MinimalAPI)
class UHotbarBagFilter : public UBagFilter
{
	GENERATED_BODY()
};