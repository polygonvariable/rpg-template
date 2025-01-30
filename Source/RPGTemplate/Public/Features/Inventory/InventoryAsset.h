#pragma once

#include "CoreMinimal.h"
#include "Internal/InternalMacro.h"
#include "Features/BaseAsset/BaseAsset.h"
#include "InventoryAsset.generated.h"


UCLASS(DisplayName = "Inventory Asset")
class RPGTEMPLATE_API UInventoryAsset : public UBaseAsset
{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (GetOptions = "InventoryLibrary.GetInventoryTypes"), Category = "Inventory")
	FString ItemType = TEXT_INVALID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (GetOptions = "InventoryLibrary.GetInventoryRarities"), Category = "Inventory")
	FString ItemRarity = TEXT_INVALID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	bool bIsStackable = false;

};