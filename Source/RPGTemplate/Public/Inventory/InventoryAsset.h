#pragma once

#include "CoreMinimal.h"
#include "Internal/InternalMacro.h"
#include "Asset/BaseAsset.h"
#include "InventoryAsset.generated.h"


UCLASS(DisplayName = "Inventory Asset")
class RPGTEMPLATE_API UInventoryAsset : public UBaseAsset
{

	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Meta = (GetOptions = "InventoryLibrary.GetInventoryTypes"), Category = "Inventory Item")
	FName ItemType = TEXT_INVALID;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Meta = (GetOptions = "InventoryLibrary.GetInventoryRarities"), Category = "Inventory Item")
	FName ItemRarity = TEXT_INVALID;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Inventory Item")
	bool bIsStackable = false;

};