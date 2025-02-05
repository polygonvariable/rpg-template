// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "Common/RenSaveGame.h"
#include "Subsystem/RenGameInstanceSubsystem.h"

#include "GameMetadata.generated.h"


/**
 *
 */
UCLASS(DisplayName = "Game Metadata")
class RENCORE_API UGameMetadata : public UPrimaryDataAsset
{

	GENERATED_BODY()
	
public:


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Subsystems")
	TSet<TSubclassOf<URenGameInstanceSubsystem>> SubsystemClasses;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Storage")
	TSubclassOf<URenSaveGame> StorageClass;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TSoftObjectPtr<UDataTable> InventoryTable;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TSet<FString> InventoryTypes = { "FOOD", "WEAPON", "SKILL" };


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TSet<FString> InventoryRarities = { "COMMON", "RARE", "ULTRA_RARE" };

};

