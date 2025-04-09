// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"

// Project Headers
#include "RenGlobal/Public/Macro/ValueMacro.h"
#include "RenCore/Public/Asset/RenDataAsset.h"
#include "RenGlobal/Public/Inventory/InventoryItemRarity.h"
#include "RenGlobal/Public/Inventory/InventoryItemType.h"

// Generated Headers
#include "InventoryAsset.generated.h"


/**
 *
 */
UCLASS(DisplayName = "Inventory Asset")
class RENASSET_API UInventoryAsset : public URenDataAsset
{

	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Inventory Item")
	TEnumAsByte<EInventoryItemType> ItemType;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Inventory Item")
	TEnumAsByte<EInventoryItemRarity> ItemRarity;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Inventory Item")
	bool bIsStackable = false;

};

