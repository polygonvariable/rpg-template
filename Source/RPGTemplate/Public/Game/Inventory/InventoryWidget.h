#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "InventorySubsystem.h"
#include "Components/ListView.h"
#include "InventoryWidget.generated.h"


UCLASS(Blueprintable, DisplayName = "Inventory Entry Object")
class RPGTEMPLATE_API UInventoryEntryObject : public UObject
{

	GENERATED_BODY()

public:

	UPROPERTY(Interp, EditAnywhere, Meta=(ExposeOnSpawn = true), Category = "Inventory Entry Object")
	FInventoryItem Item;

	UPROPERTY(Interp, EditAnywhere, Meta=(ExposeOnSpawn = true), Category = "Inventory Entry Object")
	UInventoryAsset* ItemAsset;

};

UCLASS(Abstract, DisplayName = "Inventory Widget")
class RPGTEMPLATE_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Inventory Widget|Render")
	void DisplayStoredItems();
	virtual void DisplayStoredItems_Implementation();

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

public:

	UPROPERTY(Interp, EditAnywhere, Category = "Inventory Entry Widget|Runtime")
	FInventoryItem Item;

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
