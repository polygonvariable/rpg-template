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

class UTimer;
class UEnvironmentSubsystem;
class UGameClockSubsystem;


/**
 *
 */
UCLASS()
class AEnvironmentActor : public AActor
{

	GENERATED_BODY()
	
public:

	AEnvironmentActor();



	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UEnvironmentSubsystem> EnvironmentSubsystem;

	UPROPERTY()
	TObjectPtr<UGameClockSubsystem> GameClockSubsystem;



	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
	TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
	TObjectPtr<USkyLightComponent> SkyLight;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
	TObjectPtr<USkyAtmosphereComponent> SkyAtmosphere;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
	TObjectPtr<UExponentialHeightFogComponent> ExponentialHeightFog;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
	TObjectPtr<UOrbitalLightComponent> Sun;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
	TObjectPtr<UOrbitalLightComponent> Moon;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> SkyMesh;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (UIMin = "0", UIMax = "24", ClampMin = "0", ClampMax = "24"))
	float Time = 0.0f;

protected:

	UPROPERTY()
	TObjectPtr<UTimer> DayCycleTimer;



	UFUNCTION()
	void InitializeDayCycle();

	UFUNCTION()
	void CleanupDayCycle();

	UFUNCTION()
	void StartDayCycle();

	UFUNCTION()
	void StopDayCycle();

	UFUNCTION()
	void HandleDayCycleTick(float CurrentTime);



	UFUNCTION()
	void RegisterClock();

	UFUNCTION()
	void UnregisterClock();

	UFUNCTION()
	void HandleClockStarted();

	UFUNCTION()
	void HandleClockStopped();



	UFUNCTION(BlueprintCallable)
	void InitializeControllers();

	UFUNCTION(BlueprintCallable)
	void CleanupControllers();

protected:

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

};

