// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CraftableAsset.h"
#include "Struct/InventoryAssetQuantity.h"
#include "EnhanceableAsset.generated.h"

class UEnhanceAsset;


/**
 * 
 */
UCLASS(DisplayName = "Enhanceable Asset")
class RENINVENTORY_API UEnhanceableAsset : public UCraftableAsset
{

	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Enhanceable")
	int32 EnhanceXpInterval = 5000;


	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Enhanceable")
	int32 EnhanceLevelInterval = 10;


	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Enhanceable")
	int32 EnhanceLevelMax = 100;


	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Enhanceable")
	TSet<UEnhanceAsset*> EnhanceCosts;


	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Meta = (GetKeyOptions = "InventoryLibrary.GetInventoryTypes"), Category = "Item Enhanceable")
	TMap<FName, int> EnhanceExternalCosts;


	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Enhanceable")
	TMap<int, FInventoryAssetQuantity> EnhanceRankings;

};