// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"

// Project Headers
#include "RenCore/Public/Priority/PrioritySystem.h"

// Generated Headers
#include "WeatherController.generated.h"

// Forward Declarations
class UMaterialParameterCollectionInstance;


/**
 * 
 */
UCLASS()
class UWeatherController : public UObjectPrioritySystem
{

	GENERATED_BODY()

public:

	void SetMaterialCollection(UMaterialParameterCollection* MaterialCollection);

protected:

	FName CurrentWeather;

	UMaterialParameterCollectionInstance* MaterialCollectionInstance;

	void HandleScalarTransition(FName ParameterName, float Target, float Alpha);
	void HandleVectorTransition(FName ParameterName, const FLinearColor& Target, float Alpha);

protected:

	virtual void HandleItemChanged(UObject* Item) override;

};

