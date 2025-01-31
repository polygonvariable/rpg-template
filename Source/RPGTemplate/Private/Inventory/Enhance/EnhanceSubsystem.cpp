// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Enhance/EnhanceSubsystem.h"

#include "Internal/InternalMacro.h"

#include "Inventory/InventoryAsset.h"
#include "Inventory/Assets/Types/EnhanceAsset.h"
#include "Inventory/Assets/Categories/EnhanceableAsset.h"
#include "Inventory/InventorySubsystem.h"
#include "Inventory/Enhance/EnhanceUtils.h"
#include "Library/EnhanceLibrary.h"


bool UEnhanceItemSubsystem::LevelUpItem_Implementation(const FName EnhanceableStorageId, const FName EnhanceStorageId)
{
	bool bFound = false;
	UInventoryAsset* REnhanceableAsset = nullptr;
	FInventoryItem EnhanceableItem = InventorySubsystem->GetItemWithAsset(EnhanceableStorageId, REnhanceableAsset, bFound);
	if (!bFound || !REnhanceableAsset)
	{
		LOG_ERROR(LogTemp, this, "Enhanceable item not found or invalid asset");
		return false;
	}

	bFound = false;
	UInventoryAsset* REnhanceAsset = nullptr;
	FInventoryItem EnhanceItem = InventorySubsystem->GetItemWithAsset(EnhanceStorageId, REnhanceAsset, bFound);
	if (!bFound || !REnhanceAsset)
	{
		LOG_ERROR(LogTemp, this, "Enhance item not found or invalid asset");
		return false;
	}

	UEnhanceableAsset* EnhanceableAsset = Cast<UEnhanceableAsset>(REnhanceableAsset);
	if(!EnhanceableAsset)
	{
		LOG_ERROR(LogTemp, this, "Inventory item is not of type enhanceable");
		return false;
	}

	UEnhanceAsset* EnhanceAsset = Cast<UEnhanceAsset>(REnhanceAsset);
	if (EnhanceAsset)
	{
		if(EnhanceableAsset->EnhanceCosts.Contains(EnhanceAsset))
		{
			int EnhancePoint = EnhanceAsset->EnhancePoints;
			return HandleLevelUp(EnhanceableStorageId, EnhanceStorageId, EnhanceableItem, EnhanceableAsset, EnhancePoint);
		}
		LOG_ERROR(LogTemp, this, "Internal enhance failed, trying to check for external enhance");
	}

	int* EnhancePoints = EnhanceableAsset->EnhanceExternalCosts.Find(EnhanceAsset->ItemType);
	if (!EnhancePoints)
	{
		LOG_ERROR(LogTemp, this, "External enhance failed and no points found");
		return false;
	}

	return HandleLevelUp(EnhanceableStorageId, EnhanceStorageId, EnhanceableItem, EnhanceableAsset, *EnhancePoints);
}

bool UEnhanceItemSubsystem::RankUpItem_Implementation(const FName EnhanceableStorageId)
{
	bool bFound = false;
	UInventoryAsset* REnhanceableAsset = nullptr;
	FInventoryItem EnhanceableItem = InventorySubsystem->GetItemWithAsset(EnhanceableStorageId, REnhanceableAsset, bFound);
	if (!bFound || !REnhanceableAsset)
	{
		LOG_ERROR(LogTemp, this, "Enhanceable item not found or invalid asset");
		return false;
	}

	UEnhanceableAsset* EnhanceableAsset = Cast<UEnhanceableAsset>(REnhanceableAsset);
	if (!EnhanceableAsset)
	{
		LOG_ERROR(LogTemp, this, "Inventory item is not of type enhanceable");
		return false;
	}

	TMap<int, FEnhanceRanking>& EnhanceRankings = EnhanceableAsset->EnhanceRankings;
	FEnhanceRanking* EnhanceRanking = EnhanceRankings.Find(EnhanceableItem.Rank);
	if (!EnhanceRanking) {
		LOG_ERROR(LogTemp, this, "Enhance rank not found");
		return false;
	}

	const TMap<FName, int> RankCostsIds = EnhanceRanking->ConvertToIds();
	if (!InventorySubsystem->RemoveItems(RankCostsIds))
	{
		LOG_ERROR(LogTemp, this, "Failed to remove rank costs");
		return false;
	}

	EnhanceableItem.Rank++;
	if (!InventorySubsystem->UpdateItem(EnhanceableStorageId, EnhanceableItem))
	{
		LOG_ERROR(LogTemp, this, "Failed to update enhanceable item");
		return false;
	}

	LOG_WARNING(LogTemp, this, "Rank up successful");
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
		LOG_ERROR(LogTemp, this, "Level up cancelled");
		return false;
	}

	EnhanceableItem.Xp = NewXp;
	EnhanceableItem.Level = NewLevel;

	if (!InventorySubsystem->RemoveItem(EnhanceStorageId, 1))
	{
		LOG_ERROR(LogTemp, this, "Failed to remove enhance item");
		return false;
	}

	if (InventorySubsystem->UpdateItem(EnhanceableStorageId, EnhanceableItem))
	{
		LOG_WARNING(LogTemp, this, "Level up success, new xp: %s, new level: %s", *FString::FromInt(EnhanceableItem.Xp), *FString::FromInt(EnhanceableItem.Level));
		return true;
	}

	LOG_ERROR(LogTemp, this, "Level up failed");
	return false;
}



void UEnhanceItemSubsystem::PostInitialize_Implementation()
{
	GET_SUBSYSTEM_FROM_GAMEINSTANCE(UInventorySubsystem, InventorySubsystem);
}
