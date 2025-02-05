// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"

// Project Headers
#include "Inventory/Asset/Category/PurchasableAsset.h"

// Generated Headers
#include "CraftableAsset.generated.h"

// Forward Declarations
class UInventoryAsset;


/**
 * 
 */
UCLASS(Abstract, DisplayName = "Craftable Asset")
class RENASSET_API UCraftableAsset : public UPurchasableAsset
{

	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Craftable")
	TMap<UInventoryAsset*, int32> CraftingCosts;

};
