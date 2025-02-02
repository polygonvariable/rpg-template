// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InstancedStruct.h"

#include "Filter/FilterRule.h"

#include "InventoryItem.generated.h"


/**
 * 
 */
USTRUCT(BlueprintType, DisplayName = "Inventory Item")
struct FInventoryItem
{

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Type = "Invalid";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Quantity = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Rank = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Xp = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FInstancedStruct CustomData;

	friend inline bool operator == (const FInventoryItem& A, const FInventoryItem& B)
	{
		return A.Id == B.Id && A.Type == B.Type;
	}

	friend inline uint32 GetTypeHash(const FInventoryItem& Item)
	{
		return HashCombine(GetTypeHash(Item.Id.ToString()), GetTypeHash(Item.Type));
	}

};


/**
 *
 */
USTRUCT(BlueprintType, DisplayName = "Inventory Table")
struct FInventoryTable : public FTableRowBase
{

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPrimaryDataAsset* InventoryAsset = nullptr;

	friend inline bool operator == (const FInventoryTable& A, const FInventoryTable& B)
	{
		return A.Id == B.Id;
	}

	friend inline uint32 GetTypeHash(const FInventoryTable& Item)
	{
		return GetTypeHash(Item.Id.ToString());
	}

};


/**
 *
 */
USTRUCT(BlueprintType, DisplayName = "Inventory Filter Rule")
struct FInventoryFilterRule
{

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FFilterNameRule FilterId = FFilterNameRule();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FFilterNameRule FilterType = FFilterNameRule();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FFilterNameRule FilterRarity = FFilterNameRule();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FFilterIntegerRule FilterRank = FFilterIntegerRule();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FFilterIntegerRule FilterLevel = FFilterIntegerRule();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FFilterIntegerRule FilterXp = FFilterIntegerRule();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FFilterIntegerRule FilterQuantity = FFilterIntegerRule();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EFilterCombination FilterCombination = EFilterCombination::And;

	bool Matches(const FInventoryItem& Item, const FName& Rarity) const
	{
		bool bPasses = (FilterCombination == EFilterCombination::And);

		if (FilterCombination == EFilterCombination::And)
		{
			if (!FilterId.Matches(Item.Id) || !FilterType.Matches(Item.Type) ||
				!FilterRarity.Matches(Rarity) || !FilterRank.Matches(Item.Rank) ||
				!FilterLevel.Matches(Item.Level) || !FilterXp.Matches(Item.Xp) ||
				!FilterQuantity.Matches(Item.Quantity))
			{
				bPasses = false;
			}
		}
		else if (FilterCombination == EFilterCombination::Or)
		{
			if (FilterId.Matches(Item.Id) || FilterType.Matches(Item.Type) ||
				FilterRarity.Matches(Rarity) || FilterRank.Matches(Item.Rank) ||
				FilterLevel.Matches(Item.Level) || FilterXp.Matches(Item.Xp) ||
				FilterQuantity.Matches(Item.Quantity))
			{
				bPasses = true;
			}
			else
			{
				bPasses = false;
			}
		}

		return bPasses;
	}

};

