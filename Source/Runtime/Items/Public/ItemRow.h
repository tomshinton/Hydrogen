#pragma once

#include <Runtime/Engine/Classes/Engine/DataTable.h>

#include "ItemRow.generated.h"

class UTexture2D;

USTRUCT()
struct FItemRow : public FTableRowBase
{
	GENERATED_BODY()

public:

	FItemRow()
		: ItemName()
		, ItemIcon(nullptr)
		, NameReadable()
		, StackSize(0)
	{};

	UPROPERTY(EditDefaultsOnly)
	FName ItemName;

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* ItemIcon;

	UPROPERTY(EditDefaultsOnly)
	FString NameReadable;

	UPROPERTY(EditDefaultsOnly)
	uint8 StackSize;
};