// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/InventoryAsset.h"
#include "PurchasableAsset.generated.h"


/**
 * 
 */
UCLASS(DisplayName = "Purchasable Asset")
class RPGTEMPLATE_API UPurchasableAsset : public UInventoryAsset
{

	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Purchasable")
	int32 PurchaseQuantity;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Purchasable")
	TMap<UInventoryAsset*, int32> PurchaseCosts;

};