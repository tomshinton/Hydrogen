#pragma once

#include "ContainerBase.generated.h"

USTRUCT()
struct FContainerBase
{
	GENERATED_BODY()

	FContainerBase()
		: ContainerID(FGuid())
	{
	};

	UPROPERTY()
	FGuid ContainerID;
};