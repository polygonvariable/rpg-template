// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"

// Project Headers
#include "RenCore/Public/Common/RenSaveGame.h"
#include "RenShared/Public/Inventory/InventoryItem.h"

// Generated Headers
#include "Storage.generated.h"


/**
 *
 */
UCLASS(DisplayName = "Storage")
class RENSTORAGE_API UStorage : public URenSaveGame
{

	GENERATED_BODY()

public:
	
	/**
	* A map of inventory items
	* <FName = UUID, Struct = FInventoryItem>
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Storage|Inventory")
	TMap<FName, FInventoryItem> InventoryItems; // 

	/**
	* A map of stamped events, which is a map of UUIDs to timestamps
	* <FName = UUID, Struct = FDateTime>
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Storage|Environment")
	TMap<FGuid, FDateTime> StampedEvents; // <FGuid = FGuid, Struct = FDateTime>

};

