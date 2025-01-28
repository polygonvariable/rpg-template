#include "Game/Inventory/InventoryWidget.h"


void UInventoryWidget::DisplayStoredItems_Implementation()
{

	UGameInstance* GameInstance = GetWorld()->GetGameInstance();
	if (!GameInstance) {
		return;
	}

	UInventorySubsystem* InventorySubsystem = CastChecked<UInventorySubsystem>(GameInstance->GetSubsystem<UInventorySubsystem>());
	if (!InventorySubsystem) {
		return;
	}

	bool bSuccess = false;
	TMap<FName, FInventoryItem> Items = InventorySubsystem->GetStoredItems(bSuccess);

	if (!bSuccess) {
		return;
	}

	for (auto Item : Items) {

		bool bFound = false;
		UInventoryAsset* ItemAsset = InventorySubsystem->GetItemAsset(Item.Value.Id, bFound);

		if (!bFound || !ItemAsset) {
			continue;
		}

		UInventoryEntryObject* EntryObject = NewObject<UInventoryEntryObject>(this);
		if (!EntryObject) {
			continue;
		}
		EntryObject->Item = Item.Value;
		EntryObject->ItemAsset = ItemAsset;
		
		HandleDisplayItem(EntryObject);

	}

}

void UInventoryWidget::HandleDisplayItem_Implementation(UInventoryEntryObject* EntryObject) {}
void UInventoryWidget::HandleSelectedItem_Implementation(UObject* Object) {}

void UInventoryEntryWidget::InitializeEntry_Implementation(UObject* Object)
{
	if (!Object) {
		return;
	}
	UInventoryEntryObject* EntryObject = CastChecked<UInventoryEntryObject>(Object);
	if (!EntryObject) {
		return;
	}

	Item = EntryObject->Item;
	ItemAsset = EntryObject->ItemAsset;

	HandleEntry(EntryObject);
}

void UInventoryEntryWidget::SelectEntry_Implementation()
{
	UListViewBase* ListViewBase = GetOwningListView();
	UObject* ListItem = GetListItem();

	if (!ListItem) {
		return;
	}

	UListView* ListView = CastChecked<UListView>(ListViewBase);
	ListView->SetSelectedItem(ListItem);
}

void UInventoryEntryWidget::HandleEntry_Implementation(UInventoryEntryObject* EntryObject) {}