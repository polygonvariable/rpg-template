#pragma once

#include "CoreMinimal.h"
#include "Features/PrimaryDataAsset/BaseAsset.h"
#include "InventoryAsset.generated.h"


UCLASS(DisplayName = "InventoryAsset")
class RPGTEMPLATE_API UInventoryAsset : public UBaseAsset
{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (GetOptions = "InventoryLibrary.GetInventoryTypes"), Category = "Inventory")
	FString ItemType = "Invalid";

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (GetOptions = "InventoryLibrary.GetInventoryRarities"), Category = "Inventory")
	FString ItemRarity = "Invalid";

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	bool bIsStackable = false;

};