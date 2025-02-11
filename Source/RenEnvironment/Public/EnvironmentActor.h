// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// Generated Headers
#include "EnvironmentActor.generated.h"

// Forward Declarations
class USceneComponent;
class USkyLightComponent;
class USkyAtmosphereComponent;
class UExponentialHeightFogComponent;
class UOrbitalLightComponent;
class UStaticMeshComponent;


/**
 *
 */
UCLASS(DisplayName = "Environment Actor")
class RENENVIRONMENT_API AEnvironmentActor : public AActor
{

	GENERATED_BODY()
	
public:

	AEnvironmentActor();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (UIMin = "0", UIMax = "24", ClampMin = "0", ClampMax = "24"), Category = "Environment|Time")
	float Time = 0.0f;


	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Default")
	TObjectPtr<USceneComponent> SceneComponent;


	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Default")
	TObjectPtr<USkyLightComponent> SkyLightComponent;


	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Default")
	TObjectPtr<USkyAtmosphereComponent> SkyAtmosphereComponent;


	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Default")
	TObjectPtr<UExponentialHeightFogComponent> ExponentialHeightFogComponent;


	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Default")
	TObjectPtr<UOrbitalLightComponent> SunLightComponent;


	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Default")
	TObjectPtr<UOrbitalLightComponent> MoonLightComponent;


	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Default")
	TObjectPtr<UStaticMeshComponent> SkyDome;

};

