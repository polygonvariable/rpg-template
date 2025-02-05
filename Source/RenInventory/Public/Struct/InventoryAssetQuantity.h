// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"

// Generated Headers
#include "InventoryAssetQuantity.generated.h"

// Forward Declarations
class UInventoryAsset;


/**
 * 
 */
USTRUCT(BlueprintType, DisplayName = "Inventory Asset Quantity")
struct FInventoryAssetQuantity
{

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<UInventoryAsset*, int32> InventoryItems;

	TMap<FName, int> ConvertToIds();

};