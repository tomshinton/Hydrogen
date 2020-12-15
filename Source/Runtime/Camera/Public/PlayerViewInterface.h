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

#if WITH_CLIENT_CODE
	virtual FTransform GetCameraTransform() const = 0;
#endif //WITH_CLIENT_CODE
};
