// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "InventoryWidget.h"

// Engine Headers
#include "Components/Image.h"
#include "Components/ListView.h"
#include "Components/PanelWidget.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"

// Project Headers
#include "RenShared/Public/Macro/GameInstanceMacro.h"
#include "RenShared/Public/Macro/LogMacro.h"

// Module Headers
#include "InventorySubsystem.h"
#include "RenAsset/Public/Inventory/InventoryAsset.h"


void UInventoryWidget::DisplayStoredItems_Implementation(bool bForceRefresh)
{
	if (!EntryObjectClass || !EntryObjectClass->IsChildOf(UInventoryEntryObject::StaticClass()))
	{
		LOG_ERROR(this, LogTemp, "EntryObjectClass is null or not a child of UInventoryEntryObject");
		return;
	}

	if (!IsValid(InventorySubsystem))
	{
		GET_SUBSYSTEM_FROM_GAMEINSTANCE(UInventorySubsystem, InventorySubsystem);
	}

	if (InventoryItems.Num() == 0 || bForceRefresh)
	{
		bool bSuccess = false;
		InventoryItems = InventorySubsystem->GetItems(bSuccess);

		if (!bSuccess)
		{
			LOG_ERROR(this, LogTemp, "Failed to get stored items");
			return;
		}
	}

	if (IsValid(InventoryContainer))
	{
		InventoryContainer->ClearListItems();
	}

	for (auto Item : InventoryItems)
	{
		bool bFound = false;
		UInventoryAsset* ItemAsset = InventorySubsystem->GetItemAsset(Item.Value.Id, bFound);

		if (!bFound || !ItemAsset)
		{
			LOG_ERROR(this, LogTemp, "Failed to get item asset");
			continue;
		}

		if (!InventoryFilterRule.Matches(Item.Value, ItemAsset->ItemRarity))
		{
			continue;
		}

		TObjectPtr<UInventoryEntryObject> EntryObject = NewObject<UInventoryEntryObject>(this, EntryObjectClass);
		if (!EntryObject)
		{
			LOG_ERROR(this, LogTemp, "Failed to create entry object");
			continue;
		}
		EntryObject->InventoryStorageId = Item.Key;
		EntryObject->InventoryItem = Item.Value;
		EntryObject->ItemAsset = ItemAsset;

		HandleDisplayItem(EntryObject);
	}
}

void UInventoryWidget::HandleDisplayItem_Implementation(UInventoryEntryObject* EntryObject)
{
	if (IsValid(InventoryContainer))
	{
		InventoryContainer->AddItem(EntryObject);
	}
}

void UInventoryWidget::HandleSelectedItem_Implementation(UObject* Object)
{
}


void UInventoryEntryWidget::InitializeEntry_Implementation(UObject* Object)
{
	if (!IsValid(Object) || !Object->IsA(UInventoryEntryObject::StaticClass()))
	{
		LOG_ERROR(this, LogTemp, "EntryObject is null or not a child of UInventoryEntryObject");
		return;
	}

	TObjectPtr<UInventoryEntryObject> EntryObject = Cast<UInventoryEntryObject>(Object);
	ItemSid = EntryObject->InventoryStorageId;
	Item = EntryObject->InventoryItem;
	ItemAsset = EntryObject->ItemAsset;

	HandleEntry(EntryObject);
}

void UInventoryEntryWidget::SelectEntry_Implementation()
{
	UListViewBase* ListViewBase = GetOwningListView();
	UObject* ListItem = GetListItem();

	if (!IsValid(ListItem) || !IsValid(ListViewBase))
	{
		LOG_ERROR(this, LogTemp, "ListItem or ListViewBase is null");
		return;
	}

	UListView* ListView = CastChecked<UListView>(ListViewBase);
	ListView->SetSelectedItem(ListItem);
}

void UInventoryEntryWidget::HandleEntry_Implementation(UInventoryEntryObject* EntryObject)
{
}


void UInventoryDetailWidget::InitializeDetail_Implementation(FInventoryItem InventoryItem, FName InventoryStorageId, UInventoryAsset* InventoryAsset)
{
	if (!IsValid(InventoryAsset))
	{
		if (IsValid(DetailSwitcher)) DetailSwitcher->SetActiveWidgetIndex(0);
		return;
	}

	if (!IsValid(InventorySubsystem))
	{
		GET_SUBSYSTEM_FROM_GAMEINSTANCE(UInventorySubsystem, InventorySubsystem);
	}

	Item = InventoryItem;
	ItemAsset = InventoryAsset;
	ItemSid = InventoryStorageId;

	HandleDetail();
}

void UInventoryDetailWidget::RefreshDetail_Implementation()
{
	if (!ItemSid.IsValid() || !IsValid(InventorySubsystem)) {
		LOG_ERROR(this, LogTemp, "Inventory Storage Id or InventorySubsystem is not valid");
		return;
	}

	bool bFound = false;
	Item = InventorySubsystem->GetItem(ItemSid, bFound);

	if (!bFound)
	{
		LOG_ERROR(this, LogTemp, "Item not found to refresh detail widget");
		return;
	}

	HandleDetail();
}

void UInventoryDetailWidget::HandleDetail_Implementation()
{
	if(IsValid(ItemAsset))
	{
		if (IsValid(ItemTitle)) ItemTitle->SetText(ItemAsset->Name);
		if (IsValid(ItemDescription)) ItemDescription->SetText(ItemAsset->Description);
		if (IsValid(ItemImage) && ItemAsset->Icon.IsValid()) ItemImage->SetBrushFromSoftTexture(ItemAsset->Icon);

		if (IsValid(ItemTypeWidget))
		{
			ItemTypeWidget->SetVisibility(ItemTypeVisibility.Contains(ItemAsset->ItemType) ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
		}

		if (IsValid(ItemRank)) ItemRank->SetText(FText::FromString(FString::FromInt(Item.Rank)));
		if (IsValid(ItemLevel)) ItemLevel->SetText(FText::FromString(FString::FromInt(Item.Level)));
		if (IsValid(ItemXp)) ItemXp->SetText(FText::FromString(FString::FromInt(Item.Xp)));
	}

	if(IsValid(DetailSwitcher)) DetailSwitcher->SetActiveWidgetIndex(IsValid(ItemAsset) ? 1 : 0);
}

