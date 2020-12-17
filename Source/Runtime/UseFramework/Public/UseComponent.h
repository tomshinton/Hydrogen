// Sowing Season - Tom Shinton 2020

#pragma once

#include <Runtime/Engine/Classes/Components/ActorComponent.h>
#include <ObjectMessaging/Public/Listener/ObjectMessagingListenerInterface.h>

#include "UseComponent.generated.h"

UCLASS(MinimalAPI, meta = (BlueprintSpawnableComponent))
class UUseComponent : public UActorComponent
	, public IObjectMessagingListenerInterface
{
	GENERATED_BODY()

public:

	UUseComponent();
	void BeginPlay() override;

	//IObjectMessagingListenerInterface
	FObjectMessagingListener& GetListener() override final { return Listener; }
	//~IObjectMessagingListenerInterface

private:

	void ClientRegisterEvents();

	FObjectMessagingListener Listener;

	TFunction<float()> GetUseTimeProvider;
};
