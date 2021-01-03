#include "UI/UICore/Public/Overlays/UI_Overlay.h"
#include "UI/UICore/Public/Overlays/OverlayEvents.h"

#include <ObjectMessaging/Public/Sender/ObjectMessagingFunctions.h>

DEFINE_LOG_CATEGORY_STATIC(OverlayLog, Log, Log)

UUI_Overlay::UUI_Overlay(const FObjectInitializer& InObjectInitialiser) 
	: Super(InObjectInitialiser)
{

}

void UUI_Overlay::OnSummon()
{
	UE_LOG(OverlayLog, Log, TEXT("Summoning %s - attempting to add to viewport"), *GetName());
	ObjectMessagingFunctions::SendMessage<FRequestOverlay>(*GetOuter(), FRequestOverlay(*this));
}

