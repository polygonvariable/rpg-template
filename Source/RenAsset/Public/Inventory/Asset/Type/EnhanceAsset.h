// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"

// Project Headers
#include "Inventory/Asset/Category/NonEnhanceableAsset.h"

// Generated Headers
#include "EnhanceAsset.generated.h"


/**
 * 
 */
UCLASS(DisplayName = "Enhance Asset")
class RENASSET_API UEnhanceAsset : public UNonEnhanceableAsset
{

	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Enhance")
	int32 EnhancePoints = 5000;

};