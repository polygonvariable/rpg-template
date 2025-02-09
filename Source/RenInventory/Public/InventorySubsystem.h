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

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Inventory Subsystem|Record")
	bool AddRecord(UInventoryAsset* InventoryAssetId, const int Quantity = 1);
	virtual bool AddRecord_Implementation(UInventoryAsset* InventoryAssetId, const int Quantity = 1);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Inventory Subsystem|Records")
	bool AddRecords(const TMap<UInventoryAsset*, int32>& InventoryAssets);
	virtual bool AddRecords_Implementation(const TMap<UInventoryAsset*, int32>& InventoryAssets);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Inventory Subsystem|Record")
	bool RemoveRecord(const FName InventoryRecordId, const int Quantity = 1);
	virtual bool RemoveRecord_Implementation(const FName InventoryRecordId, const int Quantity = 1);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Inventory Subsystem|Records")
	bool RemoveRecords(const TMap<FName, int32>& InventoryRecordIds);
	virtual bool RemoveRecords_Implementation(const TMap<FName, int32>& InventoryRecordIds);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Inventory Subsystem|Record")
	bool UpdateRecord(const FName InventoryRecordId, FInventoryRecord InventoryRecord);
	virtual bool UpdateRecord_Implementation(const FName InventoryRecordId, FInventoryRecord InventoryRecord);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintPure), Category = "Inventory Subsystem|Record")
	bool HasRecord(const FName InventoryRecordId);
	virtual bool HasRecord_Implementation(const FName InventoryRecordId);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Inventory Subsystem|Record")
	FInventoryRecord GetRecord(const FName InventoryRecordId, bool& bFound);
	virtual FInventoryRecord GetRecord_Implementation(const FName InventoryRecordId, bool& bFound);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Inventory Subsystem|Records")
	TMap<FName, FInventoryRecord> GetRecords(bool& bIsValid);
	virtual TMap<FName, FInventoryRecord> GetRecords_Implementation(bool& bIsValid);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Inventory Subsystem|Asset")
	UInventoryAsset* GetRecordAsset(const FName InventoryAssetId, bool& bFound);
	virtual UInventoryAsset* GetRecordAsset_Implementation(const FName InventoryAssetId, bool& bFound);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Inventory Subsystem|Asset")
	FInventoryRecord GetRecordWithAsset(const FName InventoryRecordId, UInventoryAsset*& InventoryAsset, bool& bFound);
	virtual FInventoryRecord GetRecordWithAsset_Implementation(const FName InventoryRecordId, UInventoryAsset*& InventoryAsset, bool& bFound);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Inventory Subsystem|Dirty")
	void OverwriteRecords(const TMap<FName, FInventoryRecord>& InventoryRecords);
	virtual void OverwriteRecords_Implementation(const TMap<FName, FInventoryRecord>& InventoryRecords);

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Inventory Subsystem|Properties")
	UDataTable* InventoryTable;


	UPROPERTY(BlueprintReadOnly, Category = "Inventory Subsystem|Runtime")
	UStorage* Storage;

public:

	virtual void PostInitialize_Implementation() override;

};

