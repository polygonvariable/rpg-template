// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhanceUtils.generated.h"

class UInventoryAsset;


USTRUCT(BlueprintType, DisplayName = "Enhance Ranking")
struct FEnhanceRanking
{

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<UInventoryAsset*, int> RankingCosts;

	TMap<FName, int> ConvertToIds() const;

};
