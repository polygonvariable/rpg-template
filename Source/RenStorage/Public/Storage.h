// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"

// Project Headers
#include "RenCore/Public/Common/RenSaveGame.h"
#include "RenGlobal/Public/Record/ClockRecord.h"
#include "RenGlobal/Public/Record/InventoryRecord.h"

// Generated Headers
#include "Storage.generated.h"


/**
 *
 */
UCLASS()
class RENSTORAGE_API UStorage : public URenSaveGame
{

	GENERATED_BODY()

public:
	
	/**
	 * A map of inventory items
	 * <FName = UUID, FInventoryRecord>
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, FInventoryRecord> InventoryRecords;

	/**
	 * A map of stamped events, which is a map of UUIDs to timestamps
	 * <FName = UUID, FDateTime>
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, FDateTime> StampedEvents;

	/**
	 * A map of clock related data according to level's name
	 * <FName = Level Name, FClockRecord>
	 */
	UPROPERTY()
	TMap<FName, FClockRecord> ClockRecords;

};

