#pragma once

#include "UIPool.generated.h"

class UUserWidget;

DECLARE_STATS_GROUP(TEXT("UIPool"), STATGROUP_UIPool, STATCAT_Advanced);

DECLARE_CYCLE_STAT(TEXT("UUIPool::GetWidget"), STAT_GetWidget, STATGROUP_UIPool);

UCLASS()
class UUIPool : public UObject
{
	GENERATED_BODY()

public:

	UUIPool(const FObjectInitializer& InObjectInitialiser);

	void Initialise(const TSubclassOf<UUserWidget>& InPoolClass, const uint32 InPoolSize);
	UIPOOLING_API bool ExpandPool();

	bool CanAddToInactivePool() const;

	template<class TWidget>
	TWidget* GetWidget()
	{
		if (InactiveWidgets.Num() == 0)
		{
			ExpandPool();
		}

		{
			SCOPE_CYCLE_COUNTER(STAT_GetWidget);
			const uint16 WidgetIndex = ActiveWidgets.Emplace(MoveTemp(InactiveWidgets[0]));
			InactiveWidgets.RemoveAt(0);
			return Cast<TWidget>(ActiveWidgets[WidgetIndex]);
		}
	}

	UPROPERTY()
	TSubclassOf<UUserWidget> PoolClass;

	UPROPERTY()
	TArray<UUserWidget*> ActiveWidgets;

	UPROPERTY()
	TArray<UUserWidget*> InactiveWidgets;

	int32 InitialPoolSize;
};
