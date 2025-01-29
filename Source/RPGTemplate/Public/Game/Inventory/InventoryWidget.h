#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Game/Inventory/InventoryUtils.h"

#include "InventoryWidget.generated.h"

class UInventoryAsset;


UCLASS(Blueprintable, DisplayName = "Inventory Entry Object")
class RPGTEMPLATE_API UInventoryEntryObject : public UObject
{

	GENERATED_BODY()

public:

	UPROPERTY(Interp, EditAnywhere, Meta = (ExposeOnSpawn = true), Category = "Inventory Entry Object")
	FInventoryItem Item;

	UPROPERTY(Interp, EditAnywhere, Meta = (ExposeOnSpawn = true), Category = "Inventory Entry Object")
	FName ItemSid;

	UPROPERTY(Interp, EditAnywhere, Meta = (ExposeOnSpawn = true), Category = "Inventory Entry Object")
	UInventoryAsset* ItemAsset;

};


UCLASS(Abstract, DisplayName = "Inventory Widget")
class RPGTEMPLATE_API UInventoryWidget : public UUserWidget
{

	GENERATED_BODY()
	
public:

	UPROPERTY(Interp, EditAnywhere, BlueprintReadOnly, Category = "Inventory Widget|Properties")
	TSubclassOf<UInventoryEntryObject> EntryObjectClass = UInventoryEntryObject::StaticClass();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Inventory Widget|Render")
	void DisplayStoredItems();
	virtual void DisplayStoredItems_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Inventory Widget|Handler")
	void HandleDisplayItem(UInventoryEntryObject* EntryObject);
	virtual void HandleDisplayItem_Implementation(UInventoryEntryObject* EntryObject);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Inventory Widget|Handler")
	void HandleSelectedItem(UObject* Object, bool bIsSelected = false);
	virtual void HandleSelectedItem_Implementation(UObject* Object, bool bIsSelected = false);

};


UCLASS(Abstract, DisplayName = "Inventory Entry Widget")
class RPGTEMPLATE_API UInventoryEntryWidget : public UUserWidget, public IUserObjectListEntry
{

	GENERATED_BODY()

public:

	UPROPERTY(Interp, EditAnywhere, Category = "Inventory Entry Widget|Runtime")
	FInventoryItem Item;

	UPROPERTY(Interp, EditAnywhere, Category = "Inventory Entry Widget|Runtime")
	FName ItemSid;

	UPROPERTY(Interp, EditAnywhere, Category = "Inventory Entry Widget|Runtime")
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

	UPROPERTY(Interp, EditAnywhere, Category = "Inventory Detail Widget|Runtime")
	FInventoryItem Item;

	UPROPERTY(Interp, EditAnywhere, Category = "Inventory Detail Widget|Runtime")
	FName ItemSid;

	UPROPERTY(Interp, EditAnywhere, Category = "Inventory Detail Widget|Runtime")
	UInventoryAsset* ItemAsset;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Inventory Detail Widget|Action")
	void InitializeDetail(UObject* Object);
	virtual void InitializeDetail_Implementation(UObject* Object);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Inventory Detail Widget|Handler")
	void HandleDetail(UInventoryEntryObject* EntryObject);
	virtual void HandleDetail_Implementation(UInventoryEntryObject* EntryObject);

};
