// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InstancedStruct.h"

// Project Headers
#include "RenEnvironment/Public/Controller/EnvironmentProfileType.h"

// Generated Headers
#include "EnvironmentActor.generated.h"

// Forward Declarations
class USceneComponent;
class USkyLightComponent;
class USkyAtmosphereComponent;
class UExponentialHeightFogComponent;
class UOrbitalLightComponent;
class UStaticMeshComponent;
class UTimer;
class UEnvironmentController;
class UEnvironmentSubsystem;


/**
 *
 */
UCLASS(DisplayName = "Environment Actor")
class RENENVIRONMENT_API AEnvironmentActor : public AActor
{

	GENERATED_BODY()
	
public:

	AEnvironmentActor();

	UPROPERTY()
	TObjectPtr<UEnvironmentSubsystem> EnvironmentSubsystem;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (UIMin = "0", UIMax = "24", ClampMin = "0", ClampMax = "24"), Category = "Environment|Time")
	float Time = 0.0f;


	UPROPERTY(BlueprintReadOnly, Category = "Default")
	TObjectPtr<USceneComponent> SceneComponent;


	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Default")
	TObjectPtr<USkyLightComponent> SkyLight;


	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Default")
	TObjectPtr<USkyAtmosphereComponent> SkyAtmosphere;


	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Default")
	TObjectPtr<UExponentialHeightFogComponent> ExponentialHeightFog;


	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Default")
	TObjectPtr<UOrbitalLightComponent> Sun;


	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Default")
	TObjectPtr<UOrbitalLightComponent> Moon;


	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Default")
	TObjectPtr<UStaticMeshComponent> SkyMesh;

protected:

	UPROPERTY(BlueprintReadWrite)
	UTimer* DayCycleTimer;


	UFUNCTION(BlueprintCallable, Category = "Action")
	void StartDayCycle();


	UFUNCTION(BlueprintCallable, Category = "Handler")
	void UpdateDayCycle(float CurrentTime, float TotalTime);


	UFUNCTION(BlueprintCallable, Category = "Action")
	void EndDayCycle();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Runtime")
	TMap<TEnumAsByte<EEnvironmentProfileType>, TObjectPtr<UEnvironmentController>> EnvironmentControllers;


	UFUNCTION(BlueprintCallable, Category = "Action")
	void InitializeEnvironmentControllers();


	UFUNCTION(BlueprintCallable, Category = "Action")
	void AddEnvironmentProfile(const TEnumAsByte<EEnvironmentProfileType> ProfileType, FInstancedStruct Profile);


	UFUNCTION(BlueprintCallable, Category = "Action")
	void RemoveEnvironmentProfile(const TEnumAsByte<EEnvironmentProfileType> ProfileType, FInstancedStruct Profile);


};

