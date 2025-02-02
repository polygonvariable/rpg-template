// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "RenShared/Public/Macro/ValueMacro.h"
#include "RenCore/Public/Asset/RenBaseAsset.h"

#include "InventoryAsset.generated.h"


UCLASS(DisplayName = "Inventory Asset")
class RENINVENTORY_API UInventoryAsset : public URenBaseAsset
{

	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Meta = (GetOptions = "InventoryLibrary.GetInventoryTypes"), Category = "Inventory Item")
	FName ItemType = TEXT_INVALID;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Meta = (GetOptions = "InventoryLibrary.GetInventoryRarities"), Category = "Inventory Item")
	FName ItemRarity = TEXT_INVALID;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Inventory Item")
	bool bIsStackable = false;

};

