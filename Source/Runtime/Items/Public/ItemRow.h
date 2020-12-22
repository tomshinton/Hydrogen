#pragma once

#include <Runtime/Engine/Classes/Engine/DataTable.h>

#include "ItemRow.generated.h"

USTRUCT()
struct FItemRow : public FTableRowBase
{
	GENERATED_BODY()

public:

	FItemRow()
		: ItemName()
		, NameReadable()
		, StackSize(0)
	{};

	UPROPERTY(EditDefaultsOnly)
	FName ItemName;

	UPROPERTY(EditDefaultsOnly)
	FString NameReadable;

	UPROPERTY(EditDefaultsOnly)
	uint8 StackSize;
};