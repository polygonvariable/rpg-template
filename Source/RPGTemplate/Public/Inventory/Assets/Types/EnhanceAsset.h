// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/Assets/Categories/NonEnhanceableAsset.h"
#include "EnhanceAsset.generated.h"


/**
 * 
 */
UCLASS(DisplayName = "Enhance Asset")
class RPGTEMPLATE_API UEnhanceAsset : public UNonEnhanceableAsset
{

	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Enhance")
	int32 EnhancePoints = 5000;

};