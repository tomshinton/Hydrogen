// Sowing Season - Tom Shinton 2020

#pragma once

#include <Runtime/CoreUObject/Public/UObject/Interface.h>

#include "PlayerViewInterface.generated.h"

UINTERFACE(MinimalAPI)
class UPlayerViewInterface : public UInterface
{
	GENERATED_BODY()
};

class IPlayerViewInterface
{
	GENERATED_BODY()

public:

	virtual FTransform GetCameraTransform() const = 0;
};
