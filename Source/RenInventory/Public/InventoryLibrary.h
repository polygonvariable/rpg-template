// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"

// Project Headers
#include "RenShared/Public/Macro/ValueMacro.h"
#include "RenCore/Public/Developer/GameMetadataSettings.h"

// Generated Headers
#include "InventoryLibrary.generated.h"


/**
 *
 */
UCLASS(DisplayName = "Inventory Library")
class RENINVENTORY_API UInventoryLibrary : public UObject
{

	GENERATED_BODY()
	
public:

	UFUNCTION(CallInEditor, BlueprintCallable, BlueprintPure)
	static TArray<FString> GetInventoryTypes()
	{
		const UGameMetadataSettings* Settings = GetDefault<UGameMetadataSettings>();
		if (!Settings)
		{
			return { TEXT_INVALID };
		}
		return Settings->InventoryTypes.Array();
	};

	UFUNCTION(CallInEditor, BlueprintCallable, BlueprintPure)
	static TArray<FString> GetInventoryRarities()
	{
		const UGameMetadataSettings* Settings = GetDefault<UGameMetadataSettings>();
		if (!Settings)
		{
			return { TEXT_INVALID };
		}
		return Settings->InventoryRarities.Array();
	};

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static TSet<FName> GetNamedInventoryTypes();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static TSet<FName> GetNamedInventoryRarities();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Make")
	static FName MakeInventoryType(UPARAM(Meta = (GetOptions = "GetInventoryTypes")) FName Type)
	{
		return Type;
	};

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Make")
	static FName MakeInventoryRarity(UPARAM(Meta = (GetOptions = "GetInventoryRarities")) FName Rarity)
	{
		return Rarity;
	};

};