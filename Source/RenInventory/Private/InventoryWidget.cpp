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


void UInventoryWidget::DisplayStoredRecords_Implementation(bool bForceRefresh)
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

	if (InventoryRecords.Num() == 0 || bForceRefresh)
	{
		bool bSuccess = false;
		InventoryRecords = InventorySubsystem->GetRecords(bSuccess);

		if (!bSuccess)
		{
			LOG_ERROR(this, LogTemp, "Failed to get stored records");
			return;
		}
	}

	if (IsValid(InventoryContainer))
	{
		InventoryContainer->ClearListItems();
	}

	for (auto Record : InventoryRecords)
	{
		bool bFound = false;
		UInventoryAsset* Asset = InventorySubsystem->GetRecordAsset(Record.Value.Id, bFound);

		if (!bFound || !Asset)
		{
			LOG_ERROR(this, LogTemp, "Failed to get record asset");
			continue;
		}

		if (!InventoryFilterRule.Matches(Record.Value, Asset->ItemRarity))
		{
			continue;
		}

		TObjectPtr<UInventoryEntryObject> EntryObject = NewObject<UInventoryEntryObject>(this, EntryObjectClass);
		if (!EntryObject)
		{
			LOG_ERROR(this, LogTemp, "Failed to create entry object");
			continue;
		}
		EntryObject->InventoryRecordId = Record.Key;
		EntryObject->InventoryRecord = Record.Value;
		EntryObject->InventoryAsset = Asset;

		HandleDisplayRecord(EntryObject);
	}
}

void UInventoryWidget::HandleDisplayRecord_Implementation(UInventoryEntryObject* EntryObject)
{
	if (IsValid(InventoryContainer))
	{
		InventoryContainer->AddItem(EntryObject);
	}
}

void UInventoryWidget::HandleSelectedRecord_Implementation(UObject* Object)
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
	InventoryRecordId = EntryObject->InventoryRecordId;
	InventoryRecord = EntryObject->InventoryRecord;
	InventoryAsset = EntryObject->InventoryAsset;

	HandleEntry(EntryObject);
}

void UInventoryEntryWidget::SelectEntry_Implementation()
{
	UListViewBase* ListViewBase = GetOwningListView();
	UObject* ListRecord = GetListItem();

	if (!IsValid(ListRecord) || !IsValid(ListViewBase))
	{
		LOG_ERROR(this, LogTemp, "ListRecord or ListViewBase is null");
		return;
	}

	UListView* ListView = CastChecked<UListView>(ListViewBase);
	ListView->SetSelectedItem(ListRecord);
}

void UInventoryEntryWidget::HandleEntry_Implementation(UInventoryEntryObject* EntryObject)
{
}


void UInventoryDetailWidget::InitializeDetail_Implementation(FInventoryRecord Record, FName RecordId, UInventoryAsset* Asset)
{
	if (!IsValid(Asset))
	{
		if (IsValid(DetailSwitcher)) DetailSwitcher->SetActiveWidgetIndex(0);
		LOG_ERROR(this, LogTemp, "Asset is null");
		return;
	}

	if (!IsValid(InventorySubsystem))
	{
		GET_SUBSYSTEM_FROM_GAMEINSTANCE(UInventorySubsystem, InventorySubsystem);
	}

	InventoryAsset = Asset;
	InventoryRecord = Record;
	InventoryRecordId = RecordId;

	HandleDetail();
}

void UInventoryDetailWidget::RefreshDetail_Implementation()
{
	if (!InventoryRecordId.IsValid() || !IsValid(InventorySubsystem)) {
		LOG_ERROR(this, LogTemp, "InventoryRecordId or InventorySubsystem is not valid");
		return;
	}

	bool bFound = false;
	InventoryRecord = InventorySubsystem->GetRecord(InventoryRecordId, bFound);

	if (!bFound)
	{
		LOG_ERROR(this, LogTemp, "Record not found to refresh detail widget");
		return;
	}

	HandleDetail();
}

void UInventoryDetailWidget::HandleDetail_Implementation()
{
	if(IsValid(InventoryAsset))
	{
		if (IsValid(AssetTitle)) AssetTitle->SetText(InventoryAsset->Name);
		if (IsValid(AssetDescription)) AssetDescription->SetText(InventoryAsset->Description);
		if (IsValid(AssetImage) && InventoryAsset->Icon.IsValid()) AssetImage->SetBrushFromSoftTexture(InventoryAsset->Icon);

		if (IsValid(AssetTypeWidget))
		{
			AssetTypeWidget->SetVisibility(AssetTypeVisibility.Contains(InventoryAsset->ItemType) ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
		}

		if (IsValid(RecordRank)) RecordRank->SetText(FText::FromString(FString::FromInt(InventoryRecord.EnhanceRecord.Rank)));
		if (IsValid(RecordLevel)) RecordLevel->SetText(FText::FromString(FString::FromInt(InventoryRecord.EnhanceRecord.Level)));
		if (IsValid(RecordExperience)) RecordExperience->SetText(FText::FromString(FString::FromInt(InventoryRecord.EnhanceRecord.Experience)));
	}

	if(IsValid(DetailSwitcher)) DetailSwitcher->SetActiveWidgetIndex(IsValid(InventoryAsset) ? 1 : 0);
}

