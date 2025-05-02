// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "InstancedStruct.h"

// Project Headers
#include "RenEnvironment/Public/Profile/WeatherProfile.h"

// Generated Headers
#include "WeatherSubsystem.generated.h"

// Forward Declarations
class UTimer;
class UPrioritySystem;
class UWeatherController;
class UMaterialParameterCollectionInstance;



/**
 *
 */
UCLASS(Blueprintable)
class UWeatherSubsystem : public UWorldSubsystem
{

	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void SetMaterialCollection(UMaterialParameterCollection* MaterialCollection);



	UFUNCTION(BlueprintCallable)
	void AddWeather(UWeatherAsset* WeatherAsset, int Priority);

	UFUNCTION(BlueprintCallable)
	void RemoveWeather(int Priority);

protected:

	UMaterialParameterCollectionInstance* MaterialCollectionInstance;



	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTimer> WeatherTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UWeatherController> WeatherController;



	UFUNCTION()
	void InitializeWeatherTimer(bool bAutoStart = false);

	UFUNCTION()
	void HandleWeatherTimer(float CurrentTime);

protected:

	virtual bool DoesSupportWorldType(EWorldType::Type WorldType) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	virtual void Deinitialize() override;

public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeatherCanChange);
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnWeatherCanChange OnWeatherCanChange;

};

