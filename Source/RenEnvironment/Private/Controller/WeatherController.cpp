// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Controller/WeatherController.h"

// Engine Headers
#include "Kismet/KismetMaterialLibrary.h"
#include "Materials/MaterialParameterCollectionInstance.h"

// Project Header
#include "RenGlobal/Public/Macro/LogMacro.h"
#include "RenCore/Public/Timer/Timer.h"


void UWeatherController::Initialize()
{
	if (WeatherMaterialCollection)
	{
		MaterialCollectionInstance = GetWorld()->GetParameterCollectionInstance(WeatherMaterialCollection);
	}
}

void UWeatherController::HandleItemChanged(const FInstancedStruct& Item)
{
	if (!Item.IsValid() || !MaterialCollectionInstance)
	{
		return;
	}

	if (const FWeatherProfile* WeatherProfile = Item.GetPtr<FWeatherProfile>())
	{
		HandleScalarTransition(TEXT("WeatherAlpha"), WeatherProfile->Alpha, 1.0f);
		HandleScalarTransition(TEXT("WeatherSpecular"), WeatherProfile->Specular, 1.0f);
		HandleScalarTransition(TEXT("WeatherRoughness"), WeatherProfile->Roughness, 1.0f);
		HandleScalarTransition(TEXT("WeatherOpacity"), WeatherProfile->Opacity, 1.0f);
		HandleVectorTransition(TEXT("WeatherColor"), WeatherProfile->Color, 1.0f);
	}
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