// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "EnhanceItemSubsystem.h"

// Project Headers
#include "RenShared/Public/Macro/LogMacro.h"
#include "RenShared/Public/Macro/GameInstanceMacro.h"
#include "RenShared/Public/Inventory/InventoryItem.h"
#include "RenShared/Public/Enhance/EnhanceLibrary.h"

#include "RenInventory/Public/Assets/Categories/EnhanceableAsset.h"
#include "RenInventory/Public/Assets/Types/EnhanceAsset.h"


bool UEnhanceItemSubsystem::LevelUpItem_Implementation(const FName EnhanceableStorageId, const FName EnhanceStorageId)
{
	bool bFound = false;
	UInventoryAsset* REnhanceableAsset = nullptr;
	FInventoryItem EnhanceableItem = InventorySubsystem->GetItemWithAsset(EnhanceableStorageId, REnhanceableAsset, bFound);
	if (!bFound || !REnhanceableAsset)
	{
		LOG_ERROR(this, LogTemp, "Enhanceable item not found or invalid asset");
		return false;
	}

	bFound = false;
	UInventoryAsset* REnhanceAsset = nullptr;
	FInventoryItem EnhanceItem = InventorySubsystem->GetItemWithAsset(EnhanceStorageId, REnhanceAsset, bFound);
	if (!bFound || !REnhanceAsset)
	{
		LOG_ERROR(this, LogTemp, "Enhance item not found or invalid asset");
		return false;
	}

	UEnhanceableAsset* EnhanceableAsset = Cast<UEnhanceableAsset>(REnhanceableAsset);
	if (!EnhanceableAsset)
	{
		LOG_ERROR(this, LogTemp, "Inventory item is not of type enhanceable");
		return false;
	}

	UEnhanceAsset* EnhanceAsset = Cast<UEnhanceAsset>(REnhanceAsset);
	if (EnhanceAsset)
	{
		if (EnhanceableAsset->EnhanceCosts.Contains(EnhanceAsset))
		{
			int EnhancePoint = EnhanceAsset->EnhancePoints;
			return HandleLevelUp(EnhanceableStorageId, EnhanceStorageId, EnhanceableItem, EnhanceableAsset, EnhancePoint);
		}
		LOG_ERROR(this, LogTemp, "Internal enhance failed, trying to check for external enhance");
	}

	int* EnhancePoints = EnhanceableAsset->EnhanceExternalCosts.Find(EnhanceAsset->ItemType);
	if (!EnhancePoints)
	{
		LOG_ERROR(this, LogTemp, "External enhance failed and no points found");
		return false;
	}

	return HandleLevelUp(EnhanceableStorageId, EnhanceStorageId, EnhanceableItem, EnhanceableAsset, *EnhancePoints);

    return false;
}

bool UEnhanceItemSubsystem::RankUpItem_Implementation(const FName EnhanceableStorageId)
{
	bool bFound = false;
	UInventoryAsset* REnhanceableAsset = nullptr;
	FInventoryItem EnhanceableItem = InventorySubsystem->GetItemWithAsset(EnhanceableStorageId, REnhanceableAsset, bFound);
	if (!bFound || !REnhanceableAsset)
	{
		LOG_ERROR(this, LogTemp, "Enhanceable item not found or invalid asset");
		return false;
	}

	UEnhanceableAsset* EnhanceableAsset = Cast<UEnhanceableAsset>(REnhanceableAsset);
	if (!EnhanceableAsset)
	{
		LOG_ERROR(this, LogTemp, "Inventory item is not of type enhanceable");
		return false;
	}

	TMap<int, FInventoryAssetQuantity>& EnhanceRankings = EnhanceableAsset->EnhanceRankings;
	FInventoryAssetQuantity* EnhanceRanking = EnhanceRankings.Find(EnhanceableItem.Rank);
	if (!EnhanceRanking) {
		LOG_ERROR(this, LogTemp, "Enhance rank not found");
		return false;
	}

	const TMap<FName, int> RankCostsIds;// = EnhanceRanking->ConvertToIds();
	if (!InventorySubsystem->RemoveItems(RankCostsIds))
	{
		LOG_ERROR(this, LogTemp, "Failed to remove rank costs");
		return false;
	}

	EnhanceableItem.Rank++;
	if (!InventorySubsystem->UpdateItem(EnhanceableStorageId, EnhanceableItem))
	{
		LOG_ERROR(this, LogTemp, "Failed to update enhanceable item");
		return false;
	}

	LOG_WARNING(this, LogTemp, "Rank up successful");
	return true;
}

bool UEnhanceItemSubsystem::HandleLevelUp(const FName& EnhanceableStorageId, const FName& EnhanceStorageId, FInventoryItem EnhanceableItem, UEnhanceableAsset* EnhanceableAsset, int EnhancePoint)
{
	int NewXp = 0;
	int NewLevel = 0;
	bool bDoesLevelUpdated = false;
	bool bDoesRankShouldUpdate = false;
	bool bDoesMaxLevelReached = false;

	bool bCanLevelUp = UEnhanceLibrary::CalculateEnhance(
		EnhancePoint,
		EnhanceableItem.Xp,
		EnhanceableItem.Level,
		EnhanceableItem.Rank,
		EnhanceableAsset->EnhanceXpInterval,
		EnhanceableAsset->EnhanceLevelInterval,
		EnhanceableAsset->EnhanceLevelMax,
		NewXp,
		NewLevel,
		bDoesLevelUpdated,
		bDoesRankShouldUpdate,
		bDoesMaxLevelReached
	);

	if (!bCanLevelUp)
	{
		LOG_ERROR(this, LogTemp, "Level up cancelled");
		return false;
	}

	EnhanceableItem.Xp = NewXp;
	EnhanceableItem.Level = NewLevel;

	if (!InventorySubsystem->RemoveItem(EnhanceStorageId, 1))
	{
		LOG_ERROR(this, LogTemp, "Failed to remove enhance item");
		return false;
	}

	if (InventorySubsystem->UpdateItem(EnhanceableStorageId, EnhanceableItem))
	{
		LOG_WARNING(this, LogTemp, "Level up success, new xp: %s, new level: %s", *FString::FromInt(EnhanceableItem.Xp), *FString::FromInt(EnhanceableItem.Level));
		return true;
	}

	LOG_ERROR(this, LogTemp, "Level up failed");
	return false;
}

void UEnhanceItemSubsystem::PostInitialize_Implementation()
{
	GET_SUBSYSTEM_FROM_GAMEINSTANCE(UInventorySubsystem, InventorySubsystem);
}
