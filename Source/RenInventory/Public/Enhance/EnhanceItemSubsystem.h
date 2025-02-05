// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"

// Project Headers
#include "InventorySubsystem.h"
#include "RenCore/Public/Subsystem/RenGameInstanceSubsystem.h"

// Generated Headers
#include "EnhanceItemSubsystem.generated.h"

// Forward Declarations
class UEnhanceableAsset;


/**
 *
 */
UCLASS(DisplayName = "Enhance Item Subsystem")
class RENINVENTORY_API UEnhanceItemSubsystem : public URenGameInstanceSubsystem
{

	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, Category = "Enhance Item Subsystem|Runtime")
	UInventorySubsystem* InventorySubsystem;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction))
	bool LevelUpItem(const FName EnhanceableStorageId, const FName EnhanceStorageId);
	virtual bool LevelUpItem_Implementation(const FName EnhanceableStorageId, const FName EnhanceStorageId);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction))
	bool RankUpItem(const FName EnhanceableStorageId);
	virtual bool RankUpItem_Implementation(const FName EnhanceableStorageId);

protected:

	bool HandleLevelUp(const FName& EnhanceableStorageId, const FName& EnhanceStorageId, FInventoryItem EnhanceableItem, UEnhanceableAsset* EnhanceableAsset, int EnhancePoint);

public:

	virtual void PostInitialize_Implementation() override;

};

