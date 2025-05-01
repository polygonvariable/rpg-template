// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"

// Project Headers
#include "RenCore/Public/Priority/PrioritySystem.h"
#include "RenEnvironment/Public/Profile/WeatherProfile.h"

// Generated Headers
#include "WeatherController.generated.h"

// Forward Declarations
class UMaterialParameterCollectionInstance;


/**
 * 
 */
UCLASS()
class RENENVIRONMENT_API UWeatherController : public UPrioritySystem
{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialParameterCollection* WeatherMaterialCollection;

	UMaterialParameterCollectionInstance* MaterialCollectionInstance;


	virtual void Initialize();

protected:

	void HandleScalarTransition(FName ParameterName, float Target, float Alpha);
	void HandleVectorTransition(FName ParameterName, const FLinearColor& Target, float Alpha);

protected:

	virtual void HandleItemChanged(const FInstancedStruct& Item) override;

};

