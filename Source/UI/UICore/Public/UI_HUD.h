#pragma once

#include <Runtime/UMG/Public/Blueprint/UserWidget.h>
#include <ObjectMessaging/Public/Listener/ObjectMessagingListener.h>
#include <ObjectMessaging/Public/Listener/ObjectMessagingListenerInterface.h>
#include <UI/UIPooling/Public/UIPoolProvider.h>

#include "UI/UICore/Public/Overlays/OverlayPair.h"

#include "UI_HUD.generated.h"

class UBorder;

UCLASS(MinimalAPI, Blueprintable, abstract)
class UUI_HUD : public UUserWidget
	, public IObjectMessagingListenerInterface
{
	GENERATED_BODY()

public:

	UUI_HUD(const FObjectInitializer& InObjectInitialiser);

	UPROPERTY(meta = (BindWidget))
	UBorder* OverlayContainer;

	UPROPERTY(EditAnywhere, Category = "Overlays")
	TArray<FOverlayPair> StaticOverlays;

	//IObjectMessagingListernerInterface
	FObjectMessagingListener& GetListener() override final { return Listener; };
	//~IObjectMessagingListenerInterface

protected:

	//UWidget
	virtual void NativeConstruct() override final;
	//~UWidget

private:

	void InitialiseInput();
	void InitialiseOverlays();

	void BindInputs();
	void BindEvents();
	void ClearOverlay();

	void AddOverlay(UUI_Overlay& InOverlay);

	FObjectMessagingListener Listener;
};
