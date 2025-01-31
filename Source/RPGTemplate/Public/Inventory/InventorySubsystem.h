#pragma once

#include "CoreMinimal.h"
#include "Classes/EGameInstanceSubsystem.h"
#include "Inventory/InventoryUtils.h"

#include "InventorySubsystem.generated.h"

class UESaveGame;
class UInventoryAsset;
class UGameMetadataSettings;


UCLASS(DisplayName = "Inventory Subsystem")
class RPGTEMPLATE_API UInventorySubsystem : public UEGameInstanceSubsystem
{

	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Inventory Subsystem|Storage|Dirty")
	void OverwriteItems(const TMap<FName, FInventoryItem>& InventoryItems);
	virtual void OverwriteItems_Implementation(const TMap<FName, FInventoryItem>& InventoryItems);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Inventory Subsystem|Item")
	bool AddItem(UInventoryAsset* InventoryAsset, const int Quantity = 1);
	virtual bool AddItem_Implementation(UInventoryAsset* InventoryAsset, const int Quantity = 1);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Inventory Subsystem|Items")
	bool AddItems(const TMap<UInventoryAsset*, int32>& InventoryAssets);
	virtual bool AddItems_Implementation(const TMap<UInventoryAsset*, int32>& InventoryAssets);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Inventory Subsystem|Item")
	bool RemoveItem(const FName InventoryStorageId, const int Quantity = 1);
	virtual bool RemoveItem_Implementation(const FName InventoryStorageId, const int Quantity = 1);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Inventory Subsystem|Items")
	bool RemoveItems(const TMap<FName, int32>& InventoryStorageIds);
	virtual bool RemoveItems_Implementation(const TMap<FName, int32>& InventoryStorageIds);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Inventory Subsystem|Item")
	bool UpdateItem(const FName InventoryStorageId, FInventoryItem InventoryItem);
	virtual bool UpdateItem_Implementation(const FName InventoryStorageId, FInventoryItem InventoryItem);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintPure), Category = "Inventory Subsystem|Item")
	bool HasItem(const FName InventoryStorageId);
	virtual bool HasItem_Implementation(const FName InventoryStorageId);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Inventory Subsystem|Item")
	FInventoryItem GetItem(const FName InventoryStorageId, bool& bFound);
	virtual FInventoryItem GetItem_Implementation(const FName InventoryStorageId, bool& bFound);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Inventory Subsystem|Items")
	TMap<FName, FInventoryItem> GetItems(bool& bIsValid);
	virtual TMap<FName, FInventoryItem> GetItems_Implementation(bool& bIsValid);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Inventory Subsystem|Item")
	UInventoryAsset* GetItemAsset(const FName InventoryAssetId, bool& bFound);
	virtual UInventoryAsset* GetItemAsset_Implementation(const FName InventoryAssetId, bool& bFound);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Inventory Subsystem|Item")
	FInventoryItem GetItemWithAsset(const FName InventoryStorageId, UInventoryAsset*& InventoryAsset, bool& bFound);
	virtual FInventoryItem GetItemWithAsset_Implementation(const FName InventoryStorageId, UInventoryAsset*& InventoryAsset, bool& bFound);

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Inventory Subsystem|Properties")
	UDataTable* InventoryTable;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory Subsystem|Runtime")
	UESaveGame* Storage;

public:

	virtual void PostInitialize_Implementation() override;

};
