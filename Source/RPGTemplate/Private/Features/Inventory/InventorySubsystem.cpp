#include "Features/Inventory/InventorySubsystem.h"

#include "Internal/InternalMacro.h"
#include "Developer/GameMetadataSettings.h"
#include "Features/Subsystem/StorageSubsystem.h"
#include "Features/Inventory/InventoryAsset.h"


void UInventorySubsystem::PostInitialize_Implementation()
{
	UStorageSubsystem* StorageSubsystem = nullptr;
	GET_SUBSYSTEM_FROM_GAMEINSTANCE(UStorageSubsystem, StorageSubsystem);

	if (!StorageSubsystem)
	{
		LOG_ERROR(LogTemp, this, "StorageSubsystem is null");
		return;
	}

	bool bIsValid = false;
	Storage = StorageSubsystem->GetLocalStorage(bIsValid);

	const UGameMetadataSettings* GameMetadata = GetDefault<UGameMetadataSettings>();
	if (GameMetadata->InventoryTable.IsNull())
	{
		LOG_ERROR(LogTemp, this, "InventoryTable is null");
		return;
	}
	InventoryTable = Cast<UDataTable>(GameMetadata->InventoryTable.LoadSynchronous());

	if (!bIsValid)
	{
		LOG_ERROR(LogTemp, this, "Storage not found");
	}
	else {
		LOG_INFO(LogTemp, this, "Storage loaded");
	}
}

TMap<FName, FInventoryItem> UInventorySubsystem::GetStoredItems_Implementation(bool& bIsValid)
{
	if (Storage)
	{
		bIsValid = true;
		return Storage->InventoryItems;
	}
	bIsValid = false;
	return TMap<FName, FInventoryItem>();
}

void UInventorySubsystem::OverwriteItems_Implementation(const TMap<FName, FInventoryItem>& Items)
{
	if (!Storage)
	{
		LOG_ERROR(LogTemp, this, "Storage is null");
		return;
	}
	Storage->InventoryItems = Items;
	LOG_INFO(LogTemp, this, "Items overwritten");
}

bool UInventorySubsystem::AddItem_Implementation(UInventoryAsset* ItemAsset, int ItemQuantity)
{
	if (!Storage || !ItemAsset || ItemQuantity <= 0)
	{
		LOG_ERROR(LogTemp, this, "Storage, Asset is null or Quantity less than or equal to 0");
		return false;
	}

	TMap<FName, FInventoryItem>& Items = Storage->InventoryItems;
	FName ItemId = FName(ItemAsset->Name.ToString());
	FName ItemType = FName(ItemAsset->ItemType);

	if (ItemAsset->bIsStackable)
	{

		FInventoryItem* Item = Items.Find(ItemId);
		if (Item)
		{
			Item->Quantity += ItemQuantity;
			LOG_INFO(LogTemp, this, "Stackable item updated: %s", *ItemAsset->Name.ToString());
		}
		else {

			FInventoryItem NewItem;
			NewItem.Id = ItemId;
			NewItem.Type = ItemType;
			NewItem.Quantity = ItemQuantity;

			Items.Add(ItemId, NewItem);
			LOG_INFO(LogTemp, this, "Stackable item added: %s", *ItemAsset->Name.ToString());

		}

	}
	else {
		
		FInventoryItem Item;
		Item.Id = ItemId;
		Item.Type = ItemType;
		Item.Quantity = ItemQuantity;

		Items.Add(FName(FGuid::NewGuid().ToString()), Item);
		LOG_INFO(LogTemp, this, "Non stackable item added: %s", *ItemAsset->Name.ToString());

	}

	return true;
}

bool UInventorySubsystem::AddItems_Implementation(const TMap<UInventoryAsset*, int32>& Items)
{
	if (!Storage)
	{
		LOG_ERROR(LogTemp, this, "Storage is null");
		return false;
	}
	for (auto Item : Items)
	{
		AddItem(Item.Key, Item.Value);
	}
	return false;
}

bool UInventorySubsystem::RemoveItem_Implementation(FName ItemId, int ItemQuantity)
{
	if (!Storage)
	{
		LOG_ERROR(LogTemp, this, "Storage is null");
		return false;
	}

	if (ItemQuantity <= 0)
	{
		LOG_ERROR(LogTemp, this, "Quantity must be greater than 0");
		return false;
	}

	TMap<FName, FInventoryItem>& Items = Storage->InventoryItems;
	FInventoryItem* Item = Items.Find(ItemId);

	if(!Item)
	{
		LOG_ERROR(LogTemp, this, "Item not found: %s", *ItemId.ToString());
		return false;
	}

	if (Item->Quantity > ItemQuantity)
	{
		Item->Quantity -= ItemQuantity;
		LOG_INFO(LogTemp, this, "Item quantity reduced: %s", *ItemId.ToString());
	}
	else
	{
		Items.Remove(ItemId);
		LOG_INFO(LogTemp, this, "Item removed: %s", *ItemId.ToString());
	}

	return true;
}

bool UInventorySubsystem::RemoveItems_Implementation(const TMap<FName, int32>& Items)
{
	if (!Storage) {
		LOG_ERROR(LogTemp, this, "Storage is null");
		return false;
	}
	for (auto Item : Items)
	{
		RemoveItem(Item.Key, Item.Value);
	}
	return false;
}

bool UInventorySubsystem::UpdateItem_Implementation(FInventoryItem Item)
{
	if (!Storage)
	{
		LOG_ERROR(LogTemp, this, "Storage is null");
		return false;
	}

	TMap<FName, FInventoryItem>& Items = Storage->InventoryItems;

	if(Items.Contains(Item.Id))
	{
		Items.Add(Item.Id, Item);
		LOG_INFO(LogTemp, this, "Item updated: %s", *Item.Id.ToString());
		return true;
	}

	LOG_ERROR(LogTemp, this, "Item not found: %s", *Item.Id.ToString());
	return false;
}

bool UInventorySubsystem::HasItem_Implementation(FName ItemId)
{
	if (!Storage)
	{
		return false;
	}
	return Storage->InventoryItems.Contains(ItemId);
}

FInventoryItem UInventorySubsystem::GetItem_Implementation(FName ItemId, bool& bFound)
{
	if (!Storage)
	{
		bFound = false;
		return FInventoryItem();
	}
	FInventoryItem* Item = Storage->InventoryItems.Find(ItemId);
	bFound = (Item != nullptr);

	return Item ? *Item : FInventoryItem();
}

UInventoryAsset* UInventorySubsystem::GetItemAsset_Implementation(FName ItemId, bool& bFound)
{
	FInventoryItemTable* ItemTable = InventoryTable->FindRow<FInventoryItemTable>(ItemId, TEXT(""));
	if(ItemTable)
	{
		bFound = true;
		return ItemTable->InventoryAsset;
	}
	bFound = false;
	return nullptr;
}
