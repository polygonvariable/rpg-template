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

    UPROPERTY(EditDefaultsOnly)
    bool bEnableWeather = true;

    UPROPERTY(EditDefaultsOnly)
    UWeatherAsset* DefaultWeather;

    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<UMaterialParameterCollection> WeatherMaterialParameter;



    UPROPERTY(EditDefaultsOnly)
    bool bEnableSeason = true;

    UPROPERTY(EditDefaultsOnly)
    TArray<USeasonAsset*> DefaultSeasons;

    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<UMaterialParameterCollection> SeasonMaterialParameter;

};

