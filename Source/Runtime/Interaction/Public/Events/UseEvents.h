#pragma once

#include "UseEvents.generated.h"

USTRUCT()
struct FOnStartUse
{
	GENERATED_BODY()

public:

	FOnStartUse()
		: UseTimeProvider(nullptr)
	{};

	FOnStartUse(const TFunction<float()>& InUseTimeProvider)
		: UseTimeProvider(InUseTimeProvider)
	{};

	TFunction<float()> UseTimeProvider;
};

USTRUCT()
struct FOnEndUse
{
	GENERATED_BODY()

public:

	FOnEndUse()
		: UseDuration(0.f)
	{};

	FOnEndUse(const float InUseDuration)
		: UseDuration(InUseDuration)
	{}

	float UseDuration;
};