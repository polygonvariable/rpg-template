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
UCLASS()
class RENINVENTORY_API UInventorySubsystem : public URenGameInstanceSubsystem
{

	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	bool AddRecord(UInventoryAsset* InventoryAsset, const int Quantity = 1);

	UFUNCTION(BlueprintCallable)
	bool AddRecords(const TMap<UInventoryAsset*, int32>& InventoryAssets, const bool bAllowRollback = false);



	UFUNCTION(BlueprintCallable)
	bool RemoveRecord(const FName InventoryRecordId, const int Quantity = 1);

	UFUNCTION(BlueprintCallable)
	bool RemoveRecords(const TMap<FName, int32>& InventoryRecordIds, const bool bAllowRollback = false);



	UFUNCTION(BlueprintCallable)
	bool UpdateRecord(const FName InventoryRecordId, FInventoryRecord InventoryRecord);



	UFUNCTION(BlueprintCallable)
	bool HasRecord(const FName InventoryRecordId);



	UFUNCTION(BlueprintCallable)
	FInventoryRecord GetRecord(const FName InventoryRecordId);

	UFUNCTION(BlueprintCallable)
	TMap<FName, FInventoryRecord> GetRecords();



	UFUNCTION(BlueprintCallable)
	UInventoryAsset* GetRecordAsset(const FName InventoryAssetId);

	UFUNCTION(BlueprintCallable)
	FInventoryRecord GetRecordWithAsset(const FName InventoryRecordId, UInventoryAsset*& OutInventoryAsset, bool& bOutFound);



	UFUNCTION(BlueprintCallable)
	void OverwriteRecords(const TMap<FName, FInventoryRecord>& InventoryRecords);

protected:

	// TMap<FName, UInventoryAsset*> CachedAssetMap;

	UPROPERTY(BlueprintReadOnly)
	UDataTable* InventoryTable;

	UPROPERTY(BlueprintReadOnly)
	UStorage* Storage;

public:

	virtual void PostInitialize_Implementation() override;

};

