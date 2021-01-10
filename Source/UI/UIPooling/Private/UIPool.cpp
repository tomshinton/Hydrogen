#include "UI/UIPooling/Public/UIPool.h"

#include <Runtime/UMG/Public/Blueprint/UserWidget.h>

UUIPool::UUIPool(const FObjectInitializer& InObjectInitialiser)
	: PoolClass(nullptr)
	, ActiveWidgets()
	, InactiveWidgets()
{

}

void UUIPool::Initialise(const TSubclassOf<UUserWidget>& InPoolClass, const uint32 InPoolSize)
{
	PoolClass = InPoolClass;
	InitialPoolSize = InPoolSize;
}

bool UUIPool::ExpandPool()
{
	if (UUserWidget* NewWidget = NewObject<UUserWidget>(this, PoolClass))
	{
		InactiveWidgets.Add(NewWidget);
		return true;
	}

	return false;
}

bool UUIPool::CanAddToInactivePool() const
{
	return InactiveWidgets.Num() < InitialPoolSize;
}
