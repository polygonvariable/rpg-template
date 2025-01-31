// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Enhance/EnhanceUtils.h"

#include "Inventory/InventoryAsset.h"

TMap<FName, int> FEnhanceRanking::ConvertToIds() const
{
	TMap<FName, int> Ids;
	for (auto& Pair : RankingCosts)
	{
		Ids.Add(Pair.Key->Id, Pair.Value);
	}
	return Ids;
}
