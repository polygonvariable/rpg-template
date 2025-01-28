#pragma once

#include "CoreMinimal.h"
#include "Classes/EGameInstanceSubsystem.h"
#include "Classes/ESaveGame.h"
#include "Game/Subsystem/StorageSubsystem.h"
#include "InventoryAsset.h"
#include "InventorySubsystem.generated.h"


UCLASS(DisplayName = "Inventory Subsystem")
class RPGTEMPLATE_API UInventorySubsystem : public UEGameInstanceSubsystem
{

	GENERATED_BODY()
	
public:

	UInventorySubsystem();

	UPROPERTY(Interp, EditAnywhere, Category = "Inventory Subsystem|Runtime")
	UESaveGame* Storage;

	UPROPERTY(Interp, EditAnywhere, Category = "Inventory Subsystem|Static")
	UDataTable* ItemTable;

	virtual void PostInitialize_Implementation() override;


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta=(ForceAsFunction), Category = "Inventory Subsystem|Storage")
	TMap<FName, FInventoryItem> GetStoredItems(bool& bSuccess);
	virtual TMap<FName, FInventoryItem> GetStoredItems_Implementation(bool& bSuccess);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Inventory Subsystem|Storage|Dirty")
	void OverwriteItems(const TMap<FName, FInventoryItem>& Items);
	virtual void OverwriteItems_Implementation(const TMap<FName, FInventoryItem>& Items);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Inventory Subsystem|Item")
	bool AddItem(UInventoryAsset* ItemAsset, int ItemQuantity = 1);
	virtual bool AddItem_Implementation(UInventoryAsset* ItemAsset, int ItemQuantity = 1);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Inventory Subsystem|Item")
	bool AddItems(const TMap<UInventoryAsset*, int32>& Items);
	virtual bool AddItems_Implementation(const TMap<UInventoryAsset*, int32>& Items);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Inventory Subsystem|Item")
	bool RemoveItem(FName ItemId, int ItemQuantity = 1);
	virtual bool RemoveItem_Implementation(FName ItemId, int ItemQuantity = 1);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Inventory Subsystem|Item")
	bool RemoveItems(const TMap<FName, int32>& Items);
	virtual bool RemoveItems_Implementation(const TMap<FName, int32>& Items);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Inventory Subsystem|Item")
	bool UpdateItem(FInventoryItem Item);
	virtual bool UpdateItem_Implementation(FInventoryItem Item);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintPure), Category = "Inventory Subsystem|Item")
	bool HasItem(FName ItemId);
	virtual bool HasItem_Implementation(FName ItemId);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Inventory Subsystem|Item")
	FInventoryItem GetItem(FName ItemId, bool& bFound);
	virtual FInventoryItem GetItem_Implementation(FName ItemId, bool& bFound);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Inventory Subsystem|Item")
	UInventoryAsset* GetItemAsset(FName ItemId, bool& bFound);
	virtual UInventoryAsset* GetItemAsset_Implementation(FName ItemId, bool& bFound);


};
