#pragma once

#include "CoreMinimal.h"
#include "Game/PrimaryDataAsset/BaseAsset.h"
#include "Game/Inventory/InventoryUtils.h"
#include "InventoryAsset.generated.h"


UCLASS(DisplayName = "InventoryAsset")
class RPGTEMPLATE_API UInventoryAsset : public UBaseAsset
{

	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	TEnumAsByte<EInventoryType> ItemType = EInventoryType::Material;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	TEnumAsByte<EInventoryRarity> ItemRarity = EInventoryRarity::Common;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	bool bIsStackable = false;

};
