// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "GameClockAsset.generated.h"

/**
 *
 */
UCLASS()
class RENCORE_API UGameClockAsset : public UPrimaryDataAsset
{

	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bAutoStart = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int TotalSecondsInADay = 60;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bSeparateTimePerLevel = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSet<FName> AllowedLevels;

};

