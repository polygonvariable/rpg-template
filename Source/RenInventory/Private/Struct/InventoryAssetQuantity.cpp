// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Parent Header
#include "Struct/InventoryAssetQuantity.h"

// Project Headers
#include "InventoryAsset.h"

TMap<FName, int> FInventoryAssetQuantity::ConvertToIds()
{
	TMap<FName, int> Ids;
	for (auto& Pair : InventoryItems)
	{
		Ids.Add(Pair.Key->Id, Pair.Value);
	}
	return Ids;
}

