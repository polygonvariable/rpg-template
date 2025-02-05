// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"

// Project Headers
#include "RenCore/Public/Subsystem/RenGameInstanceSubsystem.h"

// Generated Headers
#include "InventorySubsystem.generated.h"

// Forward Declarations
class UStorage;
class UInventoryAsset;
class UGameMetadataSettings;


/**
 *
 */
UCLASS(DisplayName = "Inventory Subsystem")
class RENINVENTORY_API UInventorySubsystem : public URenGameInstanceSubsystem
{

	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Inventory Subsystem|Item")
	bool AddItem(UInventoryAsset* InventoryAssetId, const int Quantity = 1);
	virtual bool AddItem_Implementation(UInventoryAsset* InventoryAssetId, const int Quantity = 1);


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


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Inventory Subsystem|Asset")
	UInventoryAsset* GetItemAsset(const FName InventoryAssetId, bool& bFound);
	virtual UInventoryAsset* GetItemAsset_Implementation(const FName InventoryAssetId, bool& bFound);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Inventory Subsystem|Asset")
	FInventoryItem GetItemWithAsset(const FName InventoryStorageId, UInventoryAsset*& InventoryAsset, bool& bFound);
	virtual FInventoryItem GetItemWithAsset_Implementation(const FName InventoryStorageId, UInventoryAsset*& InventoryAsset, bool& bFound);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Inventory Subsystem|Dirty")
	void OverwriteItems(const TMap<FName, FInventoryItem>& InventoryItems);
	virtual void OverwriteItems_Implementation(const TMap<FName, FInventoryItem>& InventoryItems);

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Inventory Subsystem|Properties")
	UDataTable* InventoryTable;


	UPROPERTY(BlueprintReadOnly, Category = "Inventory Subsystem|Runtime")
	UStorage* Storage;

public:

	virtual void PostInitialize_Implementation() override;

};

