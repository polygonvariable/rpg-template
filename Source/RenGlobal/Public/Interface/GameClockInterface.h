// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"
#include "UObject/Interface.h"

// Project Headers
#include "RenGlobal/Public/Record/ClockRecord.h"

// Generated Headers
#include "GameClockInterface.generated.h"

// Forward Declarations



UINTERFACE(MinimalAPI)
class UGameClockInterface : public UInterface
{
	GENERATED_BODY()
};

class RENGLOBAL_API IGameClockInterface
{
	GENERATED_BODY()

public:

	virtual TMap<FName, FClockRecord>& GetClockRecords() = 0;

};

