#pragma once

#include "CoreMinimal.h"
#include "InstancedStruct.h"

#include "Features/PrimaryDataAsset/BaseUtil.h"

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

USTRUCT(BlueprintType, DisplayName = "Interact Item Mapping")
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


USTRUCT(BlueprintType, DisplayName = "Interact Item Filter Rule")
struct FInventoryFilterRule
{

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBaseAssetFilterRule BaseAssetFilterRule = FBaseAssetFilterRule();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnableTypeFilter = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnableStrictType = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (GetOptions = "InventoryLibrary.GetInventoryTypes"))
	TArray<FName> IncludedTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (GetOptions = "InventoryLibrary.GetInventoryTypes"))
	TArray<FName> ExcludedTypes;

	bool MatchType(FName Type) const
	{
		if (!bEnableTypeFilter) return true;
		if (ExcludedTypes.Contains(Type)) return false;
		if (bEnableStrictType && IncludedTypes.Num() == 0) return false;
		if (IncludedTypes.Num() > 0) return IncludedTypes.Contains(Type);
		return true;
	}

	bool Matches(FName Id, FName Type) const
	{
		return BaseAssetFilterRule.Matches(Id) && MatchType(Type);
	}

};

