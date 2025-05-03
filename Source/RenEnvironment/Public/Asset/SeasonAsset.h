// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

// Project Headers
#include "RenEnvironment/Public/Profile/WeatherWeight.h"

// Generated Headers
#include "SeasonAsset.generated.h"



/**
 *
 */
UCLASS()
class USeasonAsset : public UPrimaryDataAsset
{

    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FName SeasonName = NAME_None;



    UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (UIMin = "1", ClampMin = "1"))
    int SeasonStartDay = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (UIMin = "1", ClampMin = "1"))
	int SeasonEndDay = 10;



    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UCurveFloat* SeasonCurve = nullptr;




    UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (UIMin = "-1", UIMax = "1", ClampMin = "-1", ClampMax = "1"))
    float MaterialSpecular = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (UIMin = "-1", UIMax = "1", ClampMin = "-1", ClampMax = "1"))
    float MaterialRoughness = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (UIMin = "-1", UIMax = "1", ClampMin = "-1", ClampMax = "1"))
    float MaterialOpacity = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FColor MaterialColor = FColor::White;



    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<FWeatherWeight> WeatherWeights;

};

