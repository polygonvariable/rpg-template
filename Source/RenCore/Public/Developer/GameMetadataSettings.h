// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"

// Project Headers
#include "Common/RenSaveGame.h"
#include "Subsystem/RenGameInstanceSubsystem.h"
#include "GameMetadata.h"

// Generated Headers
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


	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Game")
	TSet<FSoftClassPath> SubsystemClasses;


	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Storage")
	FSoftClassPath StorageClasses;


	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Storage")
	TSubclassOf<URenSaveGame> StorageClass;


	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TSoftObjectPtr<UDataTable> InventoryTable;


	//UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Weather")
	//TSoftObjectPtr<UMaterialParameterCollection> WeatherMaterialParameter;

};

