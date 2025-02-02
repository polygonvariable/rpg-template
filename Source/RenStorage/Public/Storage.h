// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "RenCore/Public/Common/RenSaveGame.h"
#include "RenShared/Public/Inventory/InventoryItem.h"

#include "Storage.generated.h"


/**
 *
 */
UCLASS(DisplayName = "Storage")
class RENSTORAGE_API UStorage : public URenSaveGame
{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Storage|Inventory")
	TMap<FName, FInventoryItem> InventoryItems; // <FName = UUID, Struct = FInventoryItem>

};

