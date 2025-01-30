#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Features/Inventory/InventoryUtils.h"

#include "InventoryWidget.generated.h"

class UListView;
class UInventoryAsset;
class UInventorySubsystem;


UCLASS(Blueprintable, DisplayName = "Inventory Entry Object")
class RPGTEMPLATE_API UInventoryEntryObject : public UObject
{

	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "Inventory Entry Object")
	FInventoryItem Item;

	UPROPERTY(BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "Inventory Entry Object")
	FName ItemSid;

	UPROPERTY(BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "Inventory Entry Object")
	UInventoryAsset* ItemAsset;

};


UCLASS(Abstract, DisplayName = "Inventory Widget")
class RPGTEMPLATE_API UInventoryWidget : public UUserWidget
{

	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory Widget|Properties")
	TSubclassOf<UInventoryEntryObject> EntryObjectClass = UInventoryEntryObject::StaticClass();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidgetOptional), Category = "Inventory Widget|Filter")
	FInventoryFilterRule InventoryFilterRule = FInventoryFilterRule();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (BindWidgetOptional), Category = "Inventory Widget|Binding")
	TObjectPtr<UListView> InventoryContainer;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory Widget|Runtime")
	TMap<FName, FInventoryItem> InventoryItems;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory Widget|Runtime")
	TObjectPtr<UInventorySubsystem> InventorySubsystem;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Inventory Widget|Action")
	void DisplayStoredItems(bool bForceRefresh = false);
	virtual void DisplayStoredItems_Implementation(bool bForceRefresh = false);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Inventory Widget|Handler")
	void HandleDisplayItem(UInventoryEntryObject* EntryObject);
	virtual void HandleDisplayItem_Implementation(UInventoryEntryObject* EntryObject);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Inventory Widget|Handler")
	void HandleSelectedItem(UObject* Object);
	virtual void HandleSelectedItem_Implementation(UObject* Object);

};


UCLASS(Abstract, DisplayName = "Inventory Entry Widget")
class RPGTEMPLATE_API UInventoryEntryWidget : public UUserWidget, public IUserObjectListEntry
{

	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, Category = "Inventory Entry Widget|Runtime")
	FInventoryItem Item;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory Entry Widget|Runtime")
	FName ItemSid;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory Entry Widget|Runtime")
	UInventoryAsset* ItemAsset;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Inventory Entry Widget|Action")
	void InitializeEntry(UObject* Object);
	virtual void InitializeEntry_Implementation(UObject* Object);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Inventory Entry Widget|Action")
	void SelectEntry();
	virtual void SelectEntry_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Inventory Entry Widget|Handler")
	void HandleEntry(UInventoryEntryObject* EntryObject);
	virtual void HandleEntry_Implementation(UInventoryEntryObject* EntryObject);

};


UCLASS(Abstract, DisplayName = "Inventory Detail Widget")
class RPGTEMPLATE_API UInventoryDetailWidget : public UUserWidget
{

	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Inventory Detail Widget|Action")
	void InitializeDetail(UObject* Object);
	virtual void InitializeDetail_Implementation(UObject* Object);

protected:

	UPROPERTY(BlueprintReadWrite, Category = "Inventory Detail Widget|Runtime")
	FInventoryItem Item;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory Detail Widget|Runtime")
	FName ItemSid;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory Detail Widget|Runtime")
	UInventoryAsset* ItemAsset;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Inventory Detail Widget|Handler")
	void HandleDetail(UInventoryEntryObject* EntryObject);
	virtual void HandleDetail_Implementation(UInventoryEntryObject* EntryObject);

};
