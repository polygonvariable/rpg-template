// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory/InventoryWidget.h"

#include "Components/ListView.h"

#include "Internal/InternalMacro.h"
#include "Inventory/InventoryAsset.h"
#include "Inventory/InventorySubsystem.h"


void UInventoryWidget::DisplayStoredItems_Implementation(bool bForceRefresh)
{
	if (!EntryObjectClass || !EntryObjectClass->IsChildOf(UInventoryEntryObject::StaticClass()))
	{
		LOG_ERROR(LogTemp, this, "EntryObjectClass is null or not a child of UInventoryEntryObject");
		return;
	}

	if (!InventorySubsystem)
	{
		GET_SUBSYSTEM_FROM_GAMEINSTANCE(UInventorySubsystem, InventorySubsystem);
	}

	if (InventoryItems.Num() == 0 || bForceRefresh)
	{
		bool bSuccess = false;
		InventoryItems = InventorySubsystem->GetItems(bSuccess);

		if (!bSuccess)
		{
			LOG_ERROR(LogTemp, this, "Failed to get stored items");
			return;
		}
	}

	if (InventoryContainer)
	{
		InventoryContainer->ClearListItems();
	}

	for (auto Item : InventoryItems)
	{

		bool bFound = false;
		UInventoryAsset* ItemAsset = InventorySubsystem->GetItemAsset(Item.Value.Id, bFound);

		if (!bFound || !ItemAsset)
		{
			LOG_ERROR(LogTemp, this, "Failed to get item asset");
			continue;
		}

		if (!InventoryFilterRule.Matches(
			Item.Value.Id,
			ItemAsset->ItemType,
			ItemAsset->ItemRarity,
			Item.Value.Rank,
			Item.Value.Level,
			Item.Value.Xp,
			Item.Value.Quantity
		))
		{
			continue;
		}

		UInventoryEntryObject* EntryObject = NewObject<UInventoryEntryObject>(this, EntryObjectClass);
		if (!EntryObject)
		{
			LOG_ERROR(LogTemp, this, "Failed to create entry object");
			continue;
		}
		EntryObject->Item = Item.Value;
		EntryObject->ItemSid = Item.Key;
		EntryObject->ItemAsset = ItemAsset;
		
		HandleDisplayItem(EntryObject);

	}
}

void UInventoryWidget::HandleDisplayItem_Implementation(UInventoryEntryObject* EntryObject) {
	if (InventoryContainer)
	{
		InventoryContainer->AddItem(EntryObject);
	}
}

void UInventoryWidget::HandleSelectedItem_Implementation(UObject* Object) {}

void UInventoryEntryWidget::InitializeEntry_Implementation(UObject* Object)
{
	if (!Object || !Object->IsA(UInventoryEntryObject::StaticClass()))
	{
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

	if (!ListItem || !ListViewBase)
	{
		LOG_ERROR(LogTemp, this, "ListItem or ListViewBase is null");
		return;
	}

	UListView* ListView = CastChecked<UListView>(ListViewBase);
	ListView->SetSelectedItem(ListItem);
}

void UInventoryEntryWidget::HandleEntry_Implementation(UInventoryEntryObject* EntryObject) {}

void UInventoryDetailWidget::InitializeDetail_Implementation(FInventoryItem InventoryItem, FName InventoryStorageId, UInventoryAsset* InventoryAsset)
{
	GET_SUBSYSTEM_FROM_GAMEINSTANCE(UInventorySubsystem, InventorySubsystem);

	Item = InventoryItem;
	ItemAsset = InventoryAsset;
	ItemSid = InventoryStorageId;

	HandleDetail();
}

void UInventoryDetailWidget::RefreshDetail_Implementation()
{
	if (!ItemSid.IsValid()) {
		LOG_ERROR(LogTemp, this, "Inventory Item Sid is not valid");
		return;
	}

	if (!InventorySubsystem)
	{
		LOG_ERROR(LogTemp, this, "InventorySubsystem is null");
		return;
	}

	bool bFound = false;
	Item = InventorySubsystem->GetItem(ItemSid, bFound);

	if (!bFound)
	{
		LOG_ERROR(LogTemp, this, "Item not found to refresh detail widget");
		return;
	}

	HandleDetail();
}

void UInventoryDetailWidget::HandleDetail_Implementation() {}
