// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Controller/WeatherController.h"

// Engine Headers
#include "Kismet/KismetMaterialLibrary.h"
#include "Materials/MaterialParameterCollectionInstance.h"

// Project Header
#include "RenCore/Public/Timer/Timer.h"
#include "RenGlobal/Public/Macro/LogMacro.h"

#include "RenEnvironment/Public/Asset/WeatherAsset.h"
#include "RenEnvironment/Public/Profile/WeatherProfile.h"


void UWeatherController::SetMaterialCollection(UMaterialParameterCollection* MaterialCollection)
{
	if (!MaterialCollection)
	{
		LOG_ERROR(LogTemp, TEXT("MaterialCollection is invalid"));
		return;
	}
	MaterialCollectionInstance = GetWorld()->GetParameterCollectionInstance(MaterialCollection);
}



void UWeatherController::HandleScalarTransition(FName ParameterName, float Target, float Alpha)
{
	if (!MaterialCollectionInstance) return;

	float Current = 0.0f;
	if (MaterialCollectionInstance->GetScalarParameterValue(ParameterName, Current))
	{
		MaterialCollectionInstance->SetScalarParameterValue(ParameterName, FMath::Lerp(Current, Target, Alpha));
	}
}

void UWeatherController::HandleVectorTransition(FName ParameterName, const FLinearColor& Target, float Alpha)
{
	if (!MaterialCollectionInstance) return;

	FLinearColor Current = FLinearColor::Transparent;
	if (MaterialCollectionInstance->GetVectorParameterValue(ParameterName, Current))
	{
		MaterialCollectionInstance->SetVectorParameterValue(ParameterName, FMath::CInterpTo(Current, Target, Alpha, 1.0f));
	}
}


void UWeatherController::HandleItemChanged(UObject* Item)
{
	if (!IsValid(Item) || !MaterialCollectionInstance)
	{
		LOG_ERROR(LogTemp, TEXT("Item or MaterialCollection is invalid"));
		return;
	}

	if (UWeatherAsset* WeatherAsset = Cast<UWeatherAsset>(Item))
	{
		if(WeatherAsset->WeatherName == CurrentWeather) return;
		CurrentWeather = WeatherAsset->WeatherName;

		HandleScalarTransition(TEXT("WeatherAlpha"), WeatherAsset->MaterialAlpha, 1.0f);
		HandleScalarTransition(TEXT("WeatherSpecular"), WeatherAsset->MaterialSpecular, 1.0f);
		HandleScalarTransition(TEXT("WeatherRoughness"), WeatherAsset->MaterialRoughness, 1.0f);
		HandleScalarTransition(TEXT("WeatherOpacity"), WeatherAsset->MaterialOpacity, 1.0f);
		HandleVectorTransition(TEXT("WeatherColor"), WeatherAsset->MaterialColor, 1.0f);
	}
}

