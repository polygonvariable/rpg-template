// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

// Generated Headers
#include "EnvironmentAsset.generated.h"

// Forward Declarations
class UWeatherAsset;
class USeasonAsset;



/**
 *
 */
UCLASS()
class UEnvironmentAsset : public UPrimaryDataAsset
{

	GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    bool bEnableWeather = true;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UWeatherAsset* DefaultWeather;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TObjectPtr<UMaterialParameterCollection> WeatherMaterialParameter;



    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    bool bEnableSeason = true;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<USeasonAsset*> DefaultSeasons;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TObjectPtr<UMaterialParameterCollection> SeasonMaterialParameter;

};

