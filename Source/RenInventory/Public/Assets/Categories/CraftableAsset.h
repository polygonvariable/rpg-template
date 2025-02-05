// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PurchasableAsset.h"
#include "CraftableAsset.generated.h"

class UInventoryAsset;


/**
 * 
 */
UCLASS(Abstract, DisplayName = "Craftable Asset")
class RENINVENTORY_API UCraftableAsset : public UPurchasableAsset
{

	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Craftable")
	TMap<UInventoryAsset*, int32> CraftingCosts;

};
