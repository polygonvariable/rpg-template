#include "Game/Inventory/InventorySubsystem.h"


UInventorySubsystem::UInventorySubsystem()
{
	bAllowCreation = true;
}

void UInventorySubsystem::PostInitialize_Implementation()
{

	TSubclassOf<UEGameInstanceSubsystem> SubsystemClass = UStorageSubsystem::StaticClass();
	UEGameInstanceSubsystem* Subsystem = GetSubsystem(SubsystemClass);
	if (!Subsystem) {
		UE_LOG(LogTemp, Error, TEXT("InventorySubsystem: Storage Subsystem not found"));
		return;
	}

	UStorageSubsystem* StorageSubsystem = CastChecked<UStorageSubsystem>(Subsystem);
	if (StorageSubsystem) {
		bool bIsValid = false;
		Storage = StorageSubsystem->GetLocalStorage(bIsValid);

		if (!bIsValid) {
			UE_LOG(LogTemp, Error, TEXT("InventorySubsystem: Storage not found"));
		}
		else {
			UE_LOG(LogTemp, Log, TEXT("InventorySubsystem: Storage loaded"));
		}

	}
}

TMap<FName, FInventoryItem> UInventorySubsystem::GetInventoryItems_Implementation(bool& bSuccess)
{
	if (Storage) {
		bSuccess = true;
		return Storage->InventoryItems;
	}
	bSuccess = false;
	return TMap<FName, FInventoryItem>();
}

void UInventorySubsystem::OverwriteItems_Implementation(const TMap<FName, FInventoryItem>& Items)
{
	if (!Storage) {
		UE_LOG(LogTemp, Error, TEXT("InventorySubsystem: Storage is null"));
		return;
	}
	Storage->InventoryItems = Items;
	UE_LOG(LogTemp, Warning, TEXT("InventorySubsystem: Items overwritten"));
}

bool UInventorySubsystem::AddItem_Implementation(UInventoryAsset* ItemAsset, int ItemQuantity)
{
	if (!Storage || !ItemAsset) {
		UE_LOG(LogTemp, Error, TEXT("InventorySubsystem: Storage or Asset is null"));
		return false;
	}

	if(ItemQuantity <= 0) {
		UE_LOG(LogTemp, Error, TEXT("InventorySubsystem: Quantity must be greater than 0"));
		return false;
	}

	TMap<FName, FInventoryItem>& Items = Storage->InventoryItems;
	FName ItemId = FName(ItemAsset->Name.ToString());

	if (ItemAsset->bIsStackable) {

		FInventoryItem* Item = Items.Find(ItemId);
		if (Item) {
			Item->Quantity += ItemQuantity;
			UE_LOG(LogTemp, Warning, TEXT("InventorySubsystem: Stackable item updated: %s"), *ItemAsset->Name.ToString());
		}
		else {

			FInventoryItem NewItem;
			NewItem.Id = ItemId;
			NewItem.Type = ItemAsset->ItemType;
			NewItem.Quantity = ItemQuantity;

			Items.Add(ItemId, NewItem);
			UE_LOG(LogTemp, Warning, TEXT("InventorySubsystem: Stackable item added: %s"), *ItemAsset->Name.ToString());

		}

	}
	else {
		
		FInventoryItem Item;
		Item.Id = ItemId;
		Item.Type = ItemAsset->ItemType;
		Item.Quantity = ItemQuantity;

		Items.Add(FName(FGuid::NewGuid().ToString()), Item);

		UE_LOG(LogTemp, Warning, TEXT("InventorySubsystem: Non stackable item added: %s"), *ItemAsset->Name.ToString());

	}

	return true;
}

bool UInventorySubsystem::AddItems_Implementation(const TMap<UInventoryAsset*, int32>& Items)
{
	if (!Storage) {
		UE_LOG(LogTemp, Error, TEXT("InventorySubsystem: Storage is null"));
		return false;
	}
	for (auto Item : Items) {
		AddItem(Item.Key, Item.Value);
	}
	return false;
}

bool UInventorySubsystem::RemoveItem_Implementation(FName ItemId, int ItemQuantity)
{
	if (!Storage) {
		UE_LOG(LogTemp, Error, TEXT("InventorySubsystem: Storage is null"));
		return false;
	}

	if (ItemQuantity <= 0) {
		UE_LOG(LogTemp, Error, TEXT("InventorySubsystem: Quantity must be greater than 0"));
		return false;
	}

	TMap<FName, FInventoryItem>& Items = Storage->InventoryItems;
	FInventoryItem* Item = Items.Find(ItemId);

	if(!Item) {
		UE_LOG(LogTemp, Error, TEXT("InventorySubsystem: Item not found: %s"), *ItemId.ToString());
		return false;
	}

	if (Item->Quantity > ItemQuantity) {
		Item->Quantity -= ItemQuantity;
		UE_LOG(LogTemp, Warning, TEXT("InventorySubsystem: Item quantity reduced: %s"), *ItemId.ToString());
	}
	else {
		Items.Remove(ItemId);
		UE_LOG(LogTemp, Warning, TEXT("InventorySubsystem: Item removed: %s"), *ItemId.ToString());
	}

	return true;
}

bool UInventorySubsystem::RemoveItems_Implementation(const TMap<FName, int32>& Items)
{
	if (!Storage) {
		UE_LOG(LogTemp, Error, TEXT("InventorySubsystem: Storage is null"));
		return false;
	}
	for (auto Item : Items) {
		RemoveItem(Item.Key, Item.Value);
	}
	return false;
}

bool UInventorySubsystem::UpdateItem_Implementation(FInventoryItem Item)
{
	if (!Storage) {
		UE_LOG(LogTemp, Error, TEXT("InventorySubsystem: Storage is null"));
		return false;
	}

	TMap<FName, FInventoryItem>& Items = Storage->InventoryItems;

	if(Items.Contains(Item.Id)) {
		Items.Add(Item.Id, Item);
		UE_LOG(LogTemp, Warning, TEXT("InventorySubsystem: Item updated: %s"), *Item.Id.ToString());
		return true;
	}

	UE_LOG(LogTemp, Error, TEXT("InventorySubsystem: Item not found: %s"), *Item.Id.ToString());
	return false;
}

bool UInventorySubsystem::HasItem_Implementation(FName ItemId)
{
	if (!Storage) {
		return false;
	}
	return Storage->InventoryItems.Contains(ItemId);
}

FInventoryItem UInventorySubsystem::GetItem_Implementation(FName ItemId, bool& bFound)
{
	if (!Storage) {
		bFound = false;
		return FInventoryItem();
	}
	FInventoryItem* Item = Storage->InventoryItems.Find(ItemId);
	bFound = (Item != nullptr);

	return Item ? *Item : FInventoryItem();
}

UInventoryAsset* UInventorySubsystem::GetItemAsset_Implementation(FName ItemId, bool& bFound)
{
	FInventoryItemTable* ItemTablePtr = ItemTable->FindRow<FInventoryItemTable>(ItemId, TEXT(""));
	if(ItemTablePtr) {
		bFound = true;
		return ItemTablePtr->InventoryAsset;
	}
	bFound = false;
	return nullptr;
}
