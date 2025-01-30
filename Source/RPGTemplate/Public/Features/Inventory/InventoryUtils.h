#pragma once

#include "CoreMinimal.h"
#include "InstancedStruct.h"

#include "Shared/FilterUtils.h"

#include "InventoryUtils.generated.h"

class UInventoryAsset;


USTRUCT(BlueprintType, DisplayName = "Inventory Item")
struct FInventoryItem
{

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (GetOptions = "InventoryLibrary.GetInventoryTypes"))
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


USTRUCT(BlueprintType, DisplayName = "Inventory Collection")
struct FInventoryItemTable : public FTableRowBase
{

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInventoryAsset* InventoryAsset = nullptr;

	friend inline bool operator == (const FInventoryItemTable& A, const FInventoryItemTable& B)
	{
		return A.Id == B.Id;
	}

	friend inline uint32 GetTypeHash(const FInventoryItemTable& Item)
	{
		return GetTypeHash(Item.Id.ToString());
	}

};

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

	bool Matches(FName Id, FName Type, FName Rarity, int32 Rank, int32 Level, int32 Xp, int32 Quantity) const
	{
		bool bPasses = (FilterCombination == EFilterCombination::And);

		if (FilterCombination == EFilterCombination::And)
		{
			if (!FilterId.Matches(Id) ||
				!FilterType.Matches(Type) ||
				!FilterRarity.Matches(Rarity) ||
				!FilterRank.Matches(Rank) ||
				!FilterLevel.Matches(Level) ||
				!FilterXp.Matches(Xp) ||
				!FilterQuantity.Matches(Quantity))
			{
				bPasses = false;
			}
		}
		else if (FilterCombination == EFilterCombination::Or)
		{
			if (FilterId.Matches(Id) ||
				FilterType.Matches(Type) ||
				FilterRarity.Matches(Rarity) ||
				FilterRank.Matches(Rank) ||
				FilterLevel.Matches(Level) ||
				FilterXp.Matches(Xp) ||
				FilterQuantity.Matches(Quantity))
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
