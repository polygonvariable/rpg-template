// Fill out your copyright notice in the Description page of Project Settings.


//
#include "InventorySubsystem.h"

// Project Headers
#include "RenAsset/Public/Inventory/InventoryAsset.h"
#include "RenCore/Public/Developer/GameMetadataSettings.h"
#include "RenShared/Public/Macro/GameInstanceMacro.h"
#include "RenShared/Public/Macro/LogMacro.h"
#include "RenShared/Public/Record/InventoryRecord.h"
#include "RenStorage/Public/Storage.h"
#include "RenStorage/Public/StorageSubsystem.h"



bool UInventorySubsystem::AddRecord_Implementation(UInventoryAsset* InventoryAsset, const int Quantity)
{
	if (!Storage || !InventoryAsset || Quantity <= 0)
	{
		LOG_ERROR(this, LogTemp, "Storage, Asset is null or Quantity less than or equal to 0");
		return false;
	}

	TMap<FName, FInventoryRecord>& Records = Storage->InventoryRecords;
	FName RecordId = InventoryAsset->Id;
	FName AssetType = InventoryAsset->ItemType;

	if (InventoryAsset->bIsStackable)
	{
		FInventoryRecord* Record = Records.Find(RecordId);

		if (Record)
		{
			Record->Quantity += Quantity;
			LOG_INFO(this, LogTemp, "Stackable record %s updated", *InventoryAsset->Name.ToString());
		}
		else {
			FInventoryRecord NewRecord;
			NewRecord.Id = RecordId;
			NewRecord.Type = AssetType;
			NewRecord.Quantity = Quantity;

			Records.Add(RecordId, NewRecord);
			LOG_INFO(this, LogTemp, "Stackable record %s added", *InventoryAsset->Name.ToString());
		}
	}
	else {
		FInventoryRecord NewRecord;
		NewRecord.Id = RecordId;
		NewRecord.Type = AssetType;
		NewRecord.Quantity = Quantity;

		Records.Add(FName(FGuid::NewGuid().ToString()), NewRecord);
		LOG_INFO(this, LogTemp, "Non stackable record added: %s", *InventoryAsset->Name.ToString());
	}

	return true;
}

bool UInventorySubsystem::AddRecords_Implementation(const TMap<UInventoryAsset*, int32>& InventoryAssets)
{
	if (!IsValid(Storage))
	{
		LOG_ERROR(this, LogTemp, "Storage is null");
		return false;
	}
	for (auto Record : InventoryAssets)
	{
		AddRecord(Record.Key, Record.Value);
	}
	return false;
}

bool UInventorySubsystem::RemoveRecord_Implementation(const FName InventoryRecordId, const int Quantity)
{
	if (!Storage)
	{
		LOG_ERROR(this, LogTemp, "Storage is null");
		return false;
	}

	if (Quantity <= 0)
	{
		LOG_ERROR(this, LogTemp, "Quantity must be greater than 0");
		return false;
	}

	TMap<FName, FInventoryRecord>& Records = Storage->InventoryRecords;
	FInventoryRecord* Record = Records.Find(InventoryRecordId);

	if (!Record)
	{
		LOG_ERROR(this, LogTemp, "Record not found: %s", *InventoryRecordId.ToString());
		return false;
	}

	if (Record->Quantity > Quantity)
	{
		Record->Quantity -= Quantity;
		LOG_INFO(this, LogTemp, "Record quantity reduced: %s", *InventoryRecordId.ToString());
	}
	else
	{
		Records.Remove(InventoryRecordId);
		LOG_INFO(this, LogTemp, "Record removed: %s", *InventoryRecordId.ToString());
	}

	return true;
}

bool UInventorySubsystem::RemoveRecords_Implementation(const TMap<FName, int32>& InventoryRecordIds)
{
	if (!IsValid(Storage))
	{
		LOG_ERROR(this, LogTemp, "Storage is null");
		return false;
	}

	for (auto Record : InventoryRecordIds)
	{
		RemoveRecord(Record.Key, Record.Value);
	}

	return false;
}

bool UInventorySubsystem::UpdateRecord_Implementation(const FName InventoryRecordId, FInventoryRecord InventoryRecord)
{
	if (!IsValid(Storage))
	{
		LOG_ERROR(this, LogTemp, "Storage is null");
		return false;
	}

	TMap<FName, FInventoryRecord>& Records = Storage->InventoryRecords;
	if (Records.Contains(InventoryRecordId))
	{
		Records.Add(InventoryRecordId, InventoryRecord);
		LOG_INFO(this, LogTemp, "Record updated: %s", *InventoryRecordId.ToString());
		return true;
	}

	LOG_ERROR(this, LogTemp, "Record not found: %s", *InventoryRecordId.ToString());
	return false;
}

bool UInventorySubsystem::HasRecord_Implementation(const FName InventoryRecordId)
{
	if (!IsValid(Storage))
	{
		return false;
	}

	return Storage->InventoryRecords.Contains(InventoryRecordId);
}

FInventoryRecord UInventorySubsystem::GetRecord_Implementation(const FName InventoryRecordId, bool& bFound)
{
	if (!IsValid(Storage))
	{
		bFound = false;
		return FInventoryRecord();
	}

	FInventoryRecord* Record = Storage->InventoryRecords.Find(InventoryRecordId);
	bFound = (Record != nullptr);

	return *Record;
}

TMap<FName, FInventoryRecord> UInventorySubsystem::GetRecords_Implementation(bool& bIsValid)
{
	if (!IsValid(Storage))
	{
		bIsValid = false;
		return TMap<FName, FInventoryRecord>();
	}

	bIsValid = true;
	return Storage->InventoryRecords;
}

UInventoryAsset* UInventorySubsystem::GetRecordAsset_Implementation(const FName InventoryAssetId, bool& bFound)
{
	if (!InventoryTable)
	{
		LOG_ERROR(this, LogTemp, "InventoryTable is null");
		bFound = false;
		return nullptr;
	}

	FInventoryTable* RecordTable = InventoryTable->FindRow<FInventoryTable>(InventoryAssetId, TEXT(""));
	if (RecordTable)
	{
		bFound = true;
		return Cast<UInventoryAsset>(RecordTable->InventoryAsset);
	}

	bFound = false;
	return nullptr;
}

FInventoryRecord UInventorySubsystem::GetRecordWithAsset_Implementation(const FName InventoryRecordId, UInventoryAsset*& InventoryAsset, bool& bFound)
{
	bFound = false;
	FInventoryRecord Record = GetRecord(InventoryRecordId, bFound);
	if (!bFound) {
		InventoryAsset = nullptr;
		return FInventoryRecord();
	}

	bFound = false;
	InventoryAsset = GetRecordAsset(Record.Id, bFound);
	if (!bFound) {
		InventoryAsset = nullptr;
		return Record;
	}

	return Record;
}

void UInventorySubsystem::OverwriteRecords_Implementation(const TMap<FName, FInventoryRecord>& InventoryRecords)
{
	if (!IsValid(Storage))
	{
		LOG_ERROR(this, LogTemp, "Storage is null");
		return;
	}

	Storage->InventoryRecords = InventoryRecords;
	LOG_INFO(this, LogTemp, "Records overwritten");
}

void UInventorySubsystem::PostInitialize_Implementation()
{
	Super::PostInitialize_Implementation();

	UStorageSubsystem* StorageSubsystem = nullptr;
	GET_SUBSYSTEM_FROM_GAMEINSTANCE(UStorageSubsystem, StorageSubsystem);

	bool bIsValid = false;
	Storage = StorageSubsystem->GetLocalStorage(bIsValid);
	if (!bIsValid)
	{
		LOG_ERROR(this, LogTemp, "LocalStorage not found");
		return;
	}

	const UGameMetadataSettings* GameMetadata = GetDefault<UGameMetadataSettings>();
	if (!IsValid(GameMetadata) || GameMetadata->InventoryTable.IsNull())
	{
		LOG_ERROR(this, LogTemp, "GameMetadata, StorageSubsystemClass or InventoryTable is null");
		return;
	}

	InventoryTable = Cast<UDataTable>(GameMetadata->InventoryTable.LoadSynchronous());
	if (!IsValid(InventoryTable))
	{
		LOG_ERROR(this, LogTemp, "InventoryTable cast failed");
	}
}

