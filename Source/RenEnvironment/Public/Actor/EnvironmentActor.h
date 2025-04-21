// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InstancedStruct.h"

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
class UGameClockSubsystem;


/**
 *
 */
UCLASS()
class RENENVIRONMENT_API AEnvironmentActor : public AActor
{

	GENERATED_BODY()
	
public:

	AEnvironmentActor();


	UPROPERTY()
	TObjectPtr<UEnvironmentSubsystem> EnvironmentSubsystem;


	UPROPERTY()
	TObjectPtr<UGameClockSubsystem> GameClockSubsystem;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (UIMin = "0", UIMax = "24", ClampMin = "0", ClampMax = "24"), Category = "Environment|Time")
	float Time = 0.0f;


	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Default")
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


	UPROPERTY()
	TObjectPtr<UTimer> DayCycleTimer;


	UFUNCTION(BlueprintCallable)
	void StartDayCycle();


	UFUNCTION(BlueprintCallable)
	void HandleDayCycleTick(float CurrentTime);


	UFUNCTION(BlueprintCallable)
	void EndDayCycle();


	UFUNCTION(BlueprintCallable)
	void InitializeEnvironmentControllers();


protected:

	virtual void BeginPlay() override;

};

