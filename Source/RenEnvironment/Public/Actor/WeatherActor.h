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
class UWeatherController;


/**
 *
 */
UCLASS()
class AWeatherActor : public AActor
{

	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialParameterCollection* WeatherMaterialCollection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UWeatherController> WeatherController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWeatherProfile WeatherProfile;



	UFUNCTION(BlueprintCallable)
	void SetWeather(FWeatherProfile Weather);

	UFUNCTION(BlueprintCallable)
	void ResetWeather(FWeatherProfile Weather);

protected:

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

};

