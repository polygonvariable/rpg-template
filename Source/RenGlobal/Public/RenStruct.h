// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

// Generated Headers
#include "RenStruct.generated.h"


/**
 *
 */
USTRUCT(BlueprintType, DisplayName = "Ren Struct")
struct FRenStruct
{

	GENERATED_BODY()

	bool IsValid() const { return true; }

};

