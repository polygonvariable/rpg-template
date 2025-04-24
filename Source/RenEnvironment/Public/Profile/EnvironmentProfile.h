// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"

// Generated Headers
#include "EnvironmentProfile.generated.h"

/**
 *
 */
USTRUCT(BlueprintType, DisplayName = "Environment Profile")
struct FEnvironmentProfile
{

    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int Priority = -1;

};

/**
 * 
 */
USTRUCT(BlueprintType, DisplayName = "Environment Fog Profile")
struct FEnvironmentFogProfile : public FEnvironmentProfile
{
 
    GENERATED_BODY()
 
public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float FogDensity = 0.05f;
 
};

/**
 * 
 */
USTRUCT(BlueprintType, DisplayName = "Environment Light Profile")
struct FEnvironmentLightProfile : public FEnvironmentProfile
{
 
    GENERATED_BODY()
 
public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SunIntensity = 10.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FColor SunColor = FColor::White;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MoonIntensity = 10.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FColor MoonColor = FColor::White;
 
};

/**
 * 
 */
USTRUCT(BlueprintType, DisplayName = "Environment Atmosphere Profile")
struct FEnvironmentAtmosphereProfile : public FEnvironmentProfile
{
 
    GENERATED_BODY()
 
public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MieScatteringScale = 1.0f;

};

