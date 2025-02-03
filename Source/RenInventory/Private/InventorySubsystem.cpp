// Fill out your copyright notice in the Description page of Project Settings.


//
#include "InventorySubsystem.h"

// Project Headers
#include "RenShared/Public/Macro/LogMacro.h"
#include "RenShared/Public/Macro/GameInstanceMacro.h"
#include "RenShared/Public/Inventory/InventoryItem.h"

#include "RenCore/Public/Developer/GameMetadataSettings.h"

#include "RenStorage/Public/Storage.h"
#include "RenStorage/Public/StorageSubsystem.h"

#include "InventoryAsset.h"



bool UInventorySubsystem::AddItem_Implementation(UInventoryAsset* InventoryAsset, const int Quantity)
{
	if (!Storage || !InventoryAsset || Quantity <= 0)
	{
		LOG_ERROR(this, LogTemp, "Storage, Asset is null or Quantity less than or equal to 0");
		return false;
	}

	TMap<FName, FInventoryItem>& Items = Storage->InventoryItems;
	FName ItemId = InventoryAsset->Id;
	FName ItemType = InventoryAsset->ItemType;

	if (InventoryAsset->bIsStackable)
	{
		FInventoryItem* Item = Items.Find(ItemId);

		if (Item)
		{
			Item->Quantity += Quantity;
			LOG_INFO(this, LogTemp, "Stackable item %s updated", *InventoryAsset->Name.ToString());
		}
		else {
			FInventoryItem NewItem;
			NewItem.Id = ItemId;
			NewItem.Type = ItemType;
			NewItem.Quantity = Quantity;

			Items.Add(ItemId, NewItem);
			LOG_INFO(this, LogTemp, "Stackable item %s added", *InventoryAsset->Name.ToString());
		}
	}
	else {
		FInventoryItem NewItem;
		NewItem.Id = ItemId;
		NewItem.Type = ItemType;
		NewItem.Quantity = Quantity;

		Items.Add(FName(FGuid::NewGuid().ToString()), NewItem);
		LOG_INFO(this, LogTemp, "Non stackable item added: %s", *InventoryAsset->Name.ToString());
	}

	return true;
}

bool UInventorySubsystem::AddItems_Implementation(const TMap<UInventoryAsset*, int32>& InventoryAssets)
{
	if (!IsValid(Storage))
	{
		LOG_ERROR(this, LogTemp, "Storage is null");
		return false;
	}
	for (auto Item : InventoryAssets)
	{
		AddItem(Item.Key, Item.Value);
	}
	return false;
}

bool UInventorySubsystem::RemoveItem_Implementation(const FName InventoryStorageId, const int Quantity)
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

	TMap<FName, FInventoryItem>& Items = Storage->InventoryItems;
	FInventoryItem* Item = Items.Find(InventoryStorageId);

	if (!Item)
	{
		LOG_ERROR(this, LogTemp, "Item not found: %s", *InventoryStorageId.ToString());
		return false;
	}

	if (Item->Quantity > Quantity)
	{
		Item->Quantity -= Quantity;
		LOG_INFO(this, LogTemp, "Item quantity reduced: %s", *InventoryStorageId.ToString());
	}
	else
	{
		Items.Remove(InventoryStorageId);
		LOG_INFO(this, LogTemp, "Item removed: %s", *InventoryStorageId.ToString());
	}

	return true;
}

bool UInventorySubsystem::RemoveItems_Implementation(const TMap<FName, int32>& InventoryStorageIds)
{
	if (!IsValid(Storage))
	{
		LOG_ERROR(this, LogTemp, "Storage is null");
		return false;
	}
	for (auto Item : InventoryStorageIds)
	{
		RemoveItem(Item.Key, Item.Value);
	}
	return false;
}

bool UInventorySubsystem::UpdateItem_Implementation(const FName InventoryStorageId, FInventoryItem InventoryItem)
{
	if (!IsValid(Storage))
	{
		LOG_ERROR(this, LogTemp, "Storage is null");
		return false;
	}

	TMap<FName, FInventoryItem>& Items = Storage->InventoryItems;

	if (Items.Contains(InventoryStorageId))
	{
		Items.Add(InventoryStorageId, InventoryItem);
		LOG_INFO(this, LogTemp, "Item updated: %s", *InventoryStorageId.ToString());
		return true;
	}

	LOG_ERROR(this, LogTemp, "Item not found: %s", *InventoryStorageId.ToString());
	return false;
}

bool UInventorySubsystem::HasItem_Implementation(const FName InventoryStorageId)
{
	if (!IsValid(Storage))
	{
		return false;
	}
	return Storage->InventoryItems.Contains(InventoryStorageId);
}

FInventoryItem UInventorySubsystem::GetItem_Implementation(const FName InventoryStorageId, bool& bFound)
{
	if (!IsValid(Storage))
	{
		bFound = false;
		return FInventoryItem();
	}
	FInventoryItem* Item = Storage->InventoryItems.Find(InventoryStorageId);
	bFound = (Item != nullptr);
	return *Item;
}

TMap<FName, FInventoryItem> UInventorySubsystem::GetItems_Implementation(bool& bIsValid)
{
	if (!IsValid(Storage))
	{
		bIsValid = false;
		return TMap<FName, FInventoryItem>();
	}
	bIsValid = true;
	return Storage->InventoryItems;
}

UInventoryAsset* UInventorySubsystem::GetItemAsset_Implementation(const FName InventoryAssetId, bool& bFound)
{
	if (!InventoryTable)
	{
		LOG_ERROR(this, LogTemp, "InventoryTable is null");
		bFound = false;
		return nullptr;
	}

	FInventoryTable* ItemTable = InventoryTable->FindRow<FInventoryTable>(InventoryAssetId, TEXT(""));
	if (ItemTable)
	{
		bFound = true;
		return Cast<UInventoryAsset>(ItemTable->InventoryAsset);
	}

	bFound = false;
	return nullptr;
}

FInventoryItem UInventorySubsystem::GetItemWithAsset_Implementation(const FName InventoryStorageId, UInventoryAsset*& InventoryAsset, bool& bFound)
{
	bFound = false;
	FInventoryItem Item = GetItem(InventoryStorageId, bFound);
	if (!bFound) {
		InventoryAsset = nullptr;
		return FInventoryItem();
	}

	bFound = false;
	InventoryAsset = GetItemAsset(Item.Id, bFound);
	if (!bFound) {
		InventoryAsset = nullptr;
		return Item;
	}

	return Item;
}

void UInventorySubsystem::OverwriteItems_Implementation(const TMap<FName, FInventoryItem>& InventoryItems)
{
	if (!IsValid(Storage))
	{
		LOG_ERROR(this, LogTemp, "Storage is null");
		return;
	}
	Storage->InventoryItems = InventoryItems;
	LOG_INFO(this, LogTemp, "Items overwritten");
}

void UInventorySubsystem::PostInitialize_Implementation()
{
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

