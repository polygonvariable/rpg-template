// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

// Generated Headers
#include "EnvironmentAsset.generated.h"

// Forward Declarations
class UWeatherAsset;


/**
 *
 */
UCLASS()
class UEnvironmentAsset : public UPrimaryDataAsset
{

	GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UWeatherAsset* DefaultWeather;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSet<UWeatherAsset*> WeatherAssets;

};

