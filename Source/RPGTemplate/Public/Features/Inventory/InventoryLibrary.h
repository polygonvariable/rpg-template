#pragma once

#include "CoreMinimal.h"
#include "Developer/GameMetadataSettings.h"

#include "InventoryLibrary.generated.h"


UCLASS()
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
			return { "Invalid" };
		}
		return Settings->InventoryTypes.Array();
	};

	UFUNCTION(CallInEditor, BlueprintCallable, BlueprintPure, Category = "Inventory Library")
	static TArray<FString> GetInventoryRarities()
	{
		const UGameMetadataSettings* Settings = GetDefault<UGameMetadataSettings>();
		if (!Settings)
		{
			return { "Invalid" };
		}
		return Settings->InventoryRarities.Array();
	};

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Inventory Library")
	static TSet<FName> GetNamedInventoryTypes();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Inventory Library")
	static TSet<FName> GetNamedInventoryRarities();

};