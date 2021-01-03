#include "UI/UICore/Public/UI_HUD.h"
#include "UI/UICore/Public/Overlays/OverlayEvents.h"
#include "UI/UICore/Public/Overlays/UI_Overlay.h"

#include <Runtime/UMG/Public/Components/Border.h>

DEFINE_LOG_CATEGORY_STATIC(HUDLog, Log, Log)

namespace HudBindings
{
	const FName ClearOverlayBinding = TEXT("ClearOverlay");
}

UUI_HUD::UUI_HUD(const FObjectInitializer& InObjectInitialiser)
	: Super(InObjectInitialiser)
{
}

void UUI_HUD::NativeConstruct()
{
	Super::NativeConstruct();

	InitialiseInput();
	InitialiseOverlays();

	BindEvents();
}

void UUI_HUD::InitialiseInput()
{
	InitializeInputComponent();
	BindInputs();

	bIsFocusable = true;
	SetKeyboardFocus();
}

void UUI_HUD::InitialiseOverlays()
{
	for (FOverlayPair& StaticOverlay : StaticOverlays)
	{
		if (StaticOverlay.OverlayClass != nullptr && !StaticOverlay.Binding.IsNone())
		{
			if (UUI_Overlay* OverlayWidget = NewObject<UUI_Overlay>(this, StaticOverlay.OverlayClass))
			{
				StaticOverlay.Overlay = OverlayWidget;

				InputComponent->BindAction(StaticOverlay.Binding, IE_Pressed, OverlayWidget, &UUI_Overlay::OnSummon);
			}
		}
	}
}

void UUI_HUD::BindInputs()
{
	InputComponent->BindAction(HudBindings::ClearOverlayBinding, IE_Pressed, this, &UUI_HUD::ClearOverlay);
}

void UUI_HUD::BindEvents()
{
	TWeakObjectPtr<UUI_HUD> WeakThis = TWeakObjectPtr<UUI_HUD>(this);
	Listener.Bind<FRequestOverlay>([WeakThis](const FRequestOverlay& InEv)
	{
		if (InEv.Overlay != nullptr)
		{
			if (UUI_HUD* StrongThis = WeakThis.Get())
			{
				StrongThis->AddOverlay(*InEv.Overlay);
			}
		}
	});
}

void UUI_HUD::ClearOverlay()
{
	if (OverlayContainer != nullptr)
	{
		if(OverlayContainer->GetChildrenCount() > 0)
		{
			UE_LOG(HUDLog, Log, TEXT("Clearing overlay"));
			OverlayContainer->ClearChildren();
		}
	}
}

void UUI_HUD::AddOverlay(UUI_Overlay& InOverlay)
{
	if (OverlayContainer != nullptr)
	{
		if (OverlayContainer->GetChildrenCount() == 0)
		{
			UE_LOG(HUDLog, Log, TEXT("Adding %s to overlay panel"), *InOverlay.GetName());
			OverlayContainer->AddChild(&InOverlay);
		}
	}
}
