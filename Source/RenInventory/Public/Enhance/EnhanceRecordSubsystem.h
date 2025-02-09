// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"

// Project Headers
#include "InventorySubsystem.h"
#include "RenCore/Public/Subsystem/RenGameInstanceSubsystem.h"

// Generated Headers
#include "EnhanceRecordSubsystem.generated.h"

// Forward Declarations
class UEnhanceableAsset;


/**
 *
 */
UCLASS(DisplayName = "Enhance Record Subsystem")
class RENINVENTORY_API UEnhanceRecordSubsystem : public URenGameInstanceSubsystem
{

	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, Category = "Enhance Record Subsystem|Runtime")
	UInventorySubsystem* InventorySubsystem;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction))
	bool LevelUpRecord(const FName EnhanceableRecordId, const FName EnhanceRecordId);
	virtual bool LevelUpRecord_Implementation(const FName EnhanceableRecordId, const FName EnhanceRecordId);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction))
	bool RankUpRecord(const FName EnhanceableRecordId);
	virtual bool RankUpRecord_Implementation(const FName EnhanceableRecordId);

protected:

	bool HandleLevelUp(const FName& EnhanceableRecordId, const FName& EnhanceRecordId, FInventoryRecord EnhanceableRecord, UEnhanceableAsset* EnhanceableAsset, int EnhancePoint);

public:

	virtual void PostInitialize_Implementation() override;

};

