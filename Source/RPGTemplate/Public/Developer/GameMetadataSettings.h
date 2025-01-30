#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GameFramework/SaveGame.h"
#include "GameMetadataSettings.generated.h"


UCLASS(Config = Game, defaultconfig, Meta = (DisplayName = "Game Metadata"))
class RPGTEMPLATE_API UGameMetadataSettings : public UDeveloperSettings
{

	GENERATED_BODY()

public:

	UGameMetadataSettings();

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Subsystems")
	TSet<TSubclassOf<UGameInstanceSubsystem>> SubsystemClasses;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Storage")
	TSubclassOf<USaveGame> StorageClass;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TSoftObjectPtr<UDataTable> InventoryTable;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TSet<FString> InventoryTypes = { "Food", "Weapon", "Skill"};

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TSet<FString> InventoryRarities = { "Common", "Rare", "UltraRare" };

};
