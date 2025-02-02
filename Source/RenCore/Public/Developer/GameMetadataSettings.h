// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"

#include "Common/RenSaveGame.h"
#include "Subsystem/RenGameInstanceSubsystem.h"

#include "GameMetadataSettings.generated.h"


/**
 *
 */
UCLASS(Config = Game, defaultconfig, Meta = (DisplayName = "Game Metadata"))
class RENCORE_API UGameMetadataSettings : public UDeveloperSettings
{

	GENERATED_BODY()

public:

	UGameMetadataSettings();

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Subsystems")
	TSet<TSubclassOf<URenGameInstanceSubsystem>> SubsystemClasses;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Storage")
	TSubclassOf<URenSaveGame> StorageClass;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TSoftObjectPtr<UDataTable> InventoryTable;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TSet<FString> InventoryTypes = { "FOOD", "WEAPON", "SKILL" };

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TSet<FString> InventoryRarities = { "COMMON", "RARE", "ULTRA_RARE" };

};

