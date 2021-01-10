// Sowing Season - Tom Shinton 2020

#pragma once

#include <Runtime/CoreUObject/Public/UObject/Interface.h>

#include "UIPoolProviderInterface.generated.h"

class FUIPoolProvider;

UINTERFACE(MinimalAPI, Blueprintable)
class UUIPoolProviderInterface : public UInterface
{
	GENERATED_BODY()
};

class IUIPoolProviderInterface
{
	GENERATED_BODY()

public:

	virtual FUIPoolProvider& GetPoolProvider() = 0;
};
