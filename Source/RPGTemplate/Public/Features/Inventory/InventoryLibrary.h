#pragma once

#include "CoreMinimal.h"
#include "Internal/InternalMacro.h"
#include "Developer/GameMetadataSettings.h"

#include "InventoryLibrary.generated.h"


UCLASS(DisplayName = "Inventory Library")
class RPGTEMPLATE_API UInventoryLibrary : public UObject
{

	GENERATED_BODY()
	
public:

	UFUNCTION(CallInEditor, BlueprintCallable, BlueprintPure, Category = "Inventory Library")
	static TArray<FString> GetInventoryTypes()
	{
		const UGameMetadataSettings* Settings = GetDefault<UGameMetadataSettings>();
		if (!Settings)
		{
			return { TEXT_INVALID };
		}
		return Settings->InventoryTypes.Array();
	};

	UFUNCTION(CallInEditor, BlueprintCallable, BlueprintPure, Category = "Inventory Library")
	static TArray<FString> GetInventoryRarities()
	{
		const UGameMetadataSettings* Settings = GetDefault<UGameMetadataSettings>();
		if (!Settings)
		{
			return { TEXT_INVALID };
		}
		return Settings->InventoryRarities.Array();
	};

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Inventory Library")
	static TSet<FName> GetNamedInventoryTypes();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Inventory Library")
	static TSet<FName> GetNamedInventoryRarities();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Inventory Library|Make")
	static FName MakeInventoryType(UPARAM(Meta = (GetOptions = "GetInventoryTypes")) FName Type)
	{
		return Type;
	};

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Inventory Library|Make")
	static FName MakeInventoryRarity(UPARAM(Meta = (GetOptions = "GetInventoryRarities")) FName Rarity)
	{
		return Rarity;
	};

};