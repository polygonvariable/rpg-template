#include "Game/Inventory/InventoryWidget.h"

#include "Components/ListView.h"

#include "Internal/InternalMacro.h"
#include "Game/Inventory/InventorySubsystem.h"


void UInventoryWidget::DisplayStoredItems_Implementation()
{
	UInventorySubsystem* InventorySubsystem = nullptr;
	GET_SUBSYSTEM_FROM_GAMEINSTANCE(UInventorySubsystem, InventorySubsystem);

	if (!EntryObjectClass || !EntryObjectClass->IsChildOf(UInventoryEntryObject::StaticClass())) {
		LOG_ERROR(LogTemp, this, "EntryObjectClass is null or not a child of UInventoryEntryObject");
		return;
	}

	bool bSuccess = false;
	TMap<FName, FInventoryItem> Items = InventorySubsystem->GetStoredItems(bSuccess);

	if (!bSuccess) {
		LOG_ERROR(LogTemp, this, "Failed to get stored items");
		return;
	}

	for (auto Item : Items) {

		bool bFound = false;
		UInventoryAsset* ItemAsset = InventorySubsystem->GetItemAsset(Item.Value.Id, bFound);

		if (!bFound || !ItemAsset) {
			continue;
		}

		UInventoryEntryObject* EntryObject = NewObject<UInventoryEntryObject>(this, EntryObjectClass, TEXT("EntryObject"));
		if (!EntryObject) {
			continue;
		}
		EntryObject->Item = Item.Value;
		EntryObject->ItemSid = Item.Key;
		EntryObject->ItemAsset = ItemAsset;
		
		HandleDisplayItem(EntryObject);

	}
}

void UInventoryWidget::HandleDisplayItem_Implementation(UInventoryEntryObject* EntryObject) {}
void UInventoryWidget::HandleSelectedItem_Implementation(UObject* Object, bool bIsSelected) {}

void UInventoryEntryWidget::InitializeEntry_Implementation(UObject* Object)
{
	if (!Object || !Object->IsA(UInventoryEntryObject::StaticClass())) {
		LOG_ERROR(LogTemp, this, "EntryObject is null or not a child of UInventoryEntryObject");
		return;
	}

	UInventoryEntryObject* EntryObject = Cast<UInventoryEntryObject>(Object);
	Item = EntryObject->Item;
	ItemSid = EntryObject->ItemSid;
	ItemAsset = EntryObject->ItemAsset;

	HandleEntry(EntryObject);
}

void UInventoryEntryWidget::SelectEntry_Implementation()
{
	UListViewBase* ListViewBase = GetOwningListView();
	UObject* ListItem = GetListItem();

	if (!ListItem || !ListViewBase) {
		LOG_ERROR(LogTemp, this, "ListItem or ListViewBase is null");
		return;
	}

	UListView* ListView = CastChecked<UListView>(ListViewBase);
	ListView->SetSelectedItem(ListItem);
}

void UInventoryEntryWidget::HandleEntry_Implementation(UInventoryEntryObject* EntryObject) {}

void UInventoryDetailWidget::InitializeDetail_Implementation(UObject* Object)
{
	if (!Object || !Object->IsA(UInventoryEntryObject::StaticClass())) {
		LOG_ERROR(LogTemp, this, "EntryObject is null or not a child of UInventoryEntryObject");
		return;
	}

	UInventoryEntryObject* EntryObject = Cast<UInventoryEntryObject>(Object);
	Item = EntryObject->Item;
	ItemSid = EntryObject->ItemSid;
	ItemAsset = EntryObject->ItemAsset;

	HandleDetail(EntryObject);
}

void UInventoryDetailWidget::HandleDetail_Implementation(UInventoryEntryObject* EntryObject)
{
}
