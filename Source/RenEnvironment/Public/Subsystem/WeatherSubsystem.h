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
class UPrioritySystem;
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
	void AddWeather(FWeatherProfile WeatherProfile);

	UFUNCTION(BlueprintCallable)
	void RemoveWeather(FWeatherProfile WeatherProfile);

protected:

	UMaterialParameterCollectionInstance* MaterialCollectionInstance;



	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UPrioritySystem> WeatherPriority;



	UFUNCTION()
	void HandleWeatherChanged(const FInstancedStruct& Item);

	void HandleScalarTransition(FName ParameterName, float Target, float Alpha);

	void HandleColorTransition(FName ParameterName, const FLinearColor& Target, float Alpha);

protected:

	virtual bool DoesSupportWorldType(EWorldType::Type WorldType) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	virtual void Deinitialize() override;

};

