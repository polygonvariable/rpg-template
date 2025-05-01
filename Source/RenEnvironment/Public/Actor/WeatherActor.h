// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// Project Headers
#include "RenEnvironment/Public/Profile/WeatherProfile.h"

// Generated Headers
#include "WeatherActor.generated.h"

// Forward Declarations
class UTimer;
class UPrioritySystem;
class UMaterialParameterCollectionInstance;


/**
 *
 */
UCLASS()
class RENENVIRONMENT_API AWeatherActor : public AActor
{

	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialParameterCollection* WeatherMaterialCollection;


	UMaterialParameterCollectionInstance* MaterialCollectionInstance;


	UPROPERTY()
	TObjectPtr<UTimer> TransitionTimer;

	UPROPERTY()
	TObjectPtr<UPrioritySystem> WeatherPriority;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWeatherProfile WeatherProfile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWeatherProfile PreviousWeatherProfile;



	UFUNCTION(BlueprintCallable)
	void SetWeather();

	UFUNCTION(BlueprintCallable)
	void ResetWeather();



	UFUNCTION()
	void InitializeTimer();

	UFUNCTION()
	void CleanupTimer();

	UFUNCTION()
	void StartTimer();

	UFUNCTION()
	void HandleTimerTick(float CurrentTime);



	UFUNCTION()
	void HandleScalarTransition(FName ParameterName, float Target, float Alpha);

	UFUNCTION()
	void HandleVectorTransition(FName ParameterName, FLinearColor Target, float Alpha);


protected:

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

};

