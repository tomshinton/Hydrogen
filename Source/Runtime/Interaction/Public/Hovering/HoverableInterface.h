// Sowing Season - Tom Shinton 2020

#pragma once

#include <Runtime/CoreUObject/Public/UObject/Interface.h>

#include "HoverableInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UHoverableInterface : public UInterface
{
	GENERATED_BODY()
};

class IHoverableInterface
{
	GENERATED_BODY()

public:

	virtual void OnEndHover() = 0;
	virtual void OnStartHover() = 0;
	virtual AActor* GetActor() = 0;
};
