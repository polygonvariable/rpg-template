// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

// Generated Headers
#include "GameClockAsset.generated.h"


/**
 *
 */
UCLASS()
class RENCORE_API UGameClockAsset : public UPrimaryDataAsset
{

	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
	bool bAutoStart = false;

	/*
		* Total seconds taken to complete a day
	*/
	UPROPERTY(EditAnywhere)
	int TotalSecondsInADay = 60;

	UPROPERTY(EditAnywhere)
	bool bSeparateTimePerLevel = false;

	UPROPERTY(EditAnywhere)
	TSet<FName> AllowedLevels;

};

