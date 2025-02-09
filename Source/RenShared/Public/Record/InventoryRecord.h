// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"

// Project Headers
#include "Filter/FilterRule.h"
#include "Record/RenRecord.h"
#include "Record/EnhanceRecord.h"

// Generated Headers
#include "InventoryRecord.generated.h"


/**
 * 
 */
USTRUCT(BlueprintType, DisplayName = "Inventory Record")
struct FInventoryRecord : public FRenRecord
{

	GENERATED_BODY()


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Id;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Type = "Invalid";


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Quantity = 1;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FEnhanceRecord EnhanceRecord;


	friend inline bool operator == (const FInventoryRecord& A, const FInventoryRecord& B)
	{
		return A.Id == B.Id && A.Type == B.Type;
	}

	friend inline uint32 GetTypeHash(const FInventoryRecord& Record)
	{
		return HashCombine(GetTypeHash(Record.Id.ToString()), GetTypeHash(Record.Type));
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
	UPrimaryDataAsset* InventoryAsset = nullptr;

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


	bool Matches(const FInventoryRecord& Record, const FName& Rarity) const
	{
		bool bPasses = (FilterCombination == EFilterCombination::And);

		if (FilterCombination == EFilterCombination::And)
		{
			if (!FilterId.Matches(Record.Id) || !FilterType.Matches(Record.Type) ||
				!FilterRarity.Matches(Rarity) || !FilterRank.Matches(Record.EnhanceRecord.Rank) ||
				!FilterLevel.Matches(Record.EnhanceRecord.Level) || !FilterXp.Matches(Record.EnhanceRecord.Experience) ||
				!FilterQuantity.Matches(Record.Quantity))
			{
				bPasses = false;
			}
		}
		else if (FilterCombination == EFilterCombination::Or)
		{
			if (FilterId.Matches(Record.Id) || FilterType.Matches(Record.Type) ||
				FilterRarity.Matches(Rarity) || FilterRank.Matches(Record.EnhanceRecord.Rank) ||
				FilterLevel.Matches(Record.EnhanceRecord.Level) || FilterXp.Matches(Record.EnhanceRecord.Experience) ||
				FilterQuantity.Matches(Record.Quantity))
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

