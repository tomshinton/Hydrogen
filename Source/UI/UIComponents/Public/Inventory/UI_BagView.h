#pragma once

#include <Runtime/UMG/Public/Blueprint/UserWidget.h>

#include <Runtime/CoreUObject/Public/UObject/WeakInterfacePtr.h>
#include "Runtime/Inventory/Public/Containers/Bag.h"

#include "UI_BagView.generated.h"

class IInventoryInterface;
class UUI_InventorySlot;
class UWrapBox;
struct FItemSLot;

UCLASS(MinimalAPI)
class UUI_BagView : public UUserWidget
{
	GENERATED_BODY()

public:

	UUI_BagView(const FObjectInitializer& InObjectInitialiser);

	void NativeConstruct() override;
	void SynchronizeProperties() override;
	UICOMPONENTS_API void SetAssociatedBag(IInventoryInterface* InSourceInventory, const FBag* InSourceBag);

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUI_InventorySlot> SlotClass;

	UPROPERTY(meta = (BindWidget))
	UWrapBox* SlotsBox;

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere)
	FBag TestBag;
#endif //WITH_EDITORONLY_DATA

private:

	void InitialiseView(IInventoryInterface* InSourceInventory, const FBag* InSourceBag);
	void AddSlot(IInventoryInterface* InSourceInventory, const FItemSlot* InSlot);

	TWeakInterfacePtr<IInventoryInterface> AssociatedInventory;
	FGuid AssociatedBagID;
};