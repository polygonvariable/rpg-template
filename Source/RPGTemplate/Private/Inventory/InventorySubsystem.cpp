#include "Inventory/InventorySubsystem.h"

#include "Internal/InternalMacro.h"
#include "Developer/GameMetadataSettings.h"
#include "Subsystem/StorageSubsystem.h"
#include "Inventory/InventoryAsset.h"


void UInventorySubsystem::OverwriteItems_Implementation(const TMap<FName, FInventoryItem>& InventoryItems)
{
	if (!Storage)
	{
		LOG_ERROR(LogTemp, this, "Storage is null");
		return;
	}
	Storage->InventoryItems = InventoryItems;
	LOG_INFO(LogTemp, this, "Items overwritten");
}

bool UInventorySubsystem::AddItem_Implementation(UInventoryAsset* InventoryAsset, const int Quantity)
{
	if (!Storage || !InventoryAsset || Quantity <= 0)
	{
		LOG_ERROR(LogTemp, this, "Storage, Asset is null or Quantity less than or equal to 0");
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
			LOG_INFO(LogTemp, this, "Stackable item %s updated", *InventoryAsset->Name.ToString());
		}
		else {

			FInventoryItem NewItem;
			NewItem.Id = ItemId;
			NewItem.Type = ItemType;
			NewItem.Quantity = Quantity;

			Items.Add(ItemId, NewItem);
			LOG_INFO(LogTemp, this, "Stackable item %s added", *InventoryAsset->Name.ToString());

		}

	}
	else {
		
		FInventoryItem NewItem;
		NewItem.Id = ItemId;
		NewItem.Type = ItemType;
		NewItem.Quantity = Quantity;

		Items.Add(FName(FGuid::NewGuid().ToString()), NewItem);
		LOG_INFO(LogTemp, this, "Non stackable item added: %s", *InventoryAsset->Name.ToString());

	}

	return true;
}

bool UInventorySubsystem::AddItems_Implementation(const TMap<UInventoryAsset*, int32>& InventoryAssets)
{
	if (!Storage)
	{
		LOG_ERROR(LogTemp, this, "Storage is null");
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
		LOG_ERROR(LogTemp, this, "Storage is null");
		return false;
	}

	if (Quantity <= 0)
	{
		LOG_ERROR(LogTemp, this, "Quantity must be greater than 0");
		return false;
	}

	TMap<FName, FInventoryItem>& Items = Storage->InventoryItems;
	FInventoryItem* Item = Items.Find(InventoryStorageId);

	if(!Item)
	{
		LOG_ERROR(LogTemp, this, "Item not found: %s", *InventoryStorageId.ToString());
		return false;
	}

	if (Item->Quantity > Quantity)
	{
		Item->Quantity -= Quantity;
		LOG_INFO(LogTemp, this, "Item quantity reduced: %s", *InventoryStorageId.ToString());
	}
	else
	{
		Items.Remove(InventoryStorageId);
		LOG_INFO(LogTemp, this, "Item removed: %s", *InventoryStorageId.ToString());
	}

	return true;
}

bool UInventorySubsystem::RemoveItems_Implementation(const TMap<FName, int32>& InventoryStorageIds)
{
	if (!Storage) {
		LOG_ERROR(LogTemp, this, "Storage is null");
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
	if (!Storage)
	{
		LOG_ERROR(LogTemp, this, "Storage is null");
		return false;
	}

	TMap<FName, FInventoryItem>& Items = Storage->InventoryItems;

	if(Items.Contains(InventoryStorageId))
	{
		Items.Add(InventoryStorageId, InventoryItem);
		LOG_INFO(LogTemp, this, "Item updated: %s", *InventoryStorageId.ToString());
		return true;
	}

	LOG_ERROR(LogTemp, this, "Item not found: %s", *InventoryStorageId.ToString());
	return false;
}

bool UInventorySubsystem::HasItem_Implementation(const FName InventoryStorageId)
{
	if (!Storage)
	{
		return false;
	}
	return Storage->InventoryItems.Contains(InventoryStorageId);
}

FInventoryItem UInventorySubsystem::GetItem_Implementation(const FName InventoryStorageId, bool& bFound)
{
	if (!Storage)
	{
		bFound = false;
		return FInventoryItem();
	}

	FInventoryItem* Item = Storage->InventoryItems.Find(InventoryStorageId);
	bFound = (Item != nullptr);

	return (Item) ? *Item : FInventoryItem();
}

TMap<FName, FInventoryItem> UInventorySubsystem::GetItems_Implementation(bool& bIsValid)
{
	if (Storage)
	{
		bIsValid = true;
		return Storage->InventoryItems;
	}

	bIsValid = false;
	return TMap<FName, FInventoryItem>();
}

UInventoryAsset* UInventorySubsystem::GetItemAsset_Implementation(const FName InventoryAssetId, bool& bFound)
{
	if(!InventoryTable)
	{
		LOG_ERROR(LogTemp, this, "InventoryTable is null");
		bFound = false;
		return nullptr;
	}

	FInventoryItemTable* ItemTable = InventoryTable->FindRow<FInventoryItemTable>(InventoryAssetId, TEXT(""));
	if(ItemTable)
	{
		bFound = true;
		return ItemTable->InventoryAsset;
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

void UInventorySubsystem::PostInitialize_Implementation()
{
	UStorageSubsystem* StorageSubsystem = nullptr;
	GET_SUBSYSTEM_FROM_GAMEINSTANCE(UStorageSubsystem, StorageSubsystem);

	bool bIsValid = false;
	Storage = StorageSubsystem->GetLocalStorage(bIsValid);
	if(!bIsValid)
	{
		LOG_ERROR(LogTemp, this, "Storage not found");
		return;
	}

	const UGameMetadataSettings* GameMetadata = GetDefault<UGameMetadataSettings>();
	if (!GameMetadata || GameMetadata->InventoryTable.IsNull())
	{
		LOG_ERROR(LogTemp, this, "GameMetadata or InventoryTable is null");
		return;
	}

	InventoryTable = Cast<UDataTable>(GameMetadata->InventoryTable.LoadSynchronous());
	if (!InventoryTable)
	{
		LOG_ERROR(LogTemp, this, "InventoryTable cast failed");
		return;
	}
}