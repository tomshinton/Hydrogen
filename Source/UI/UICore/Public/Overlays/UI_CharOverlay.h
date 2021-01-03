#pragma once

#include "UI/UICore/Public/Overlays/UI_Overlay.h"

#include "UI_CharOverlay.generated.h"

class IInventoryInterface;
class UUI_BagView;
class UVerticalBox;
struct FBag;

UCLASS()
class UUI_CharOverlay : public UUI_Overlay
{
	GENERATED_BODY()

public:
	
	UUI_CharOverlay(const FObjectInitializer& InObjectInitialiser);

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* AllBags;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	TSubclassOf<UUI_BagView> BagViewClass;

protected:
	
	void NativeConstruct() override;

private:

	void BuildInventoryPanel();
	void AddBagView(IInventoryInterface* InSourceInventory, const FBag* InSourceBag);
};