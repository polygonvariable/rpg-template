// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Actor/WeatherActor.h"

// Engine Headers
#include "Kismet/KismetMaterialLibrary.h"
#include "Materials/MaterialParameterCollectionInstance.h"

// Project Header
#include "RenCore/Public/Priority/PrioritySystem.h"
#include "RenCore/Public/Timer/Timer.h"
#include "RenGlobal/Public/Macro/LogMacro.h"



void AWeatherActor::SetWeather()
{

	HandleScalarTransition(TEXT("WeatherAlpha"), WeatherProfile.Alpha, 1.0f);
	HandleScalarTransition(TEXT("WeatherSpecular"), WeatherProfile.Specular, 1.0f);
	HandleScalarTransition(TEXT("WeatherRoughness"), WeatherProfile.Roughness, 1.0f);
	HandleScalarTransition(TEXT("WeatherOpacity"), WeatherProfile.Opacity, 1.0f);
	HandleVectorTransition(TEXT("WeatherColor"), WeatherProfile.Color, 1.0f);

}

void AWeatherActor::ResetWeather()
{
}


void AWeatherActor::InitializeTimer()
{
	if (IsValid(TransitionTimer))
	{
		LOG_ERROR(LogTemp, TEXT("TransitionTimer is already valid"));
		return;
	}

	TransitionTimer = NewObject<UTimer>(this);
	if (!IsValid(TransitionTimer))
	{
		LOG_ERROR(LogTemp, TEXT("Failed to create TransitionTimer"));
		return;
	}

	TransitionTimer->OnTick.AddDynamic(this, &AWeatherActor::HandleTimerTick);
}

void AWeatherActor::CleanupTimer()
{
	if (!IsValid(TransitionTimer))
	{
		LOG_ERROR(LogTemp, TEXT("TransitionTimer is not valid"));
		return;
	}

	TransitionTimer->StopTimer(true);
	TransitionTimer->OnTick.RemoveAll(this);
	TransitionTimer->MarkAsGarbage();
}

void AWeatherActor::StartTimer()
{
	if (!IsValid(TransitionTimer) || !IsValid(GetWorld()) || !MaterialCollectionInstance)
	{
		LOG_ERROR(LogTemp, TEXT("TransitionTimer, world or MaterialCollectionInstance is not valid"));
		return;
	}

	TransitionTimer->StartTimer(0.1f, 10);
}

void AWeatherActor::HandleTimerTick(float CurrentTime)
{
	float Alpha = TransitionTimer->GetNormalizedAlpha();
	if (UWorld* World = GetWorld())
	{



	}
	else
	{
		TransitionTimer->StopTimer();
	}
}



void AWeatherActor::HandleScalarTransition(FName ParameterName, float Target, float Alpha)
{
	if(!MaterialCollectionInstance) return;

	float Current = 0.0f;
	if (MaterialCollectionInstance->GetScalarParameterValue(ParameterName, Current))
	{
		MaterialCollectionInstance->SetScalarParameterValue(ParameterName, FMath::Lerp(Current, Target, Alpha));
	}
}

void AWeatherActor::HandleVectorTransition(FName ParameterName, FLinearColor Target, float Alpha)
{
	if (!MaterialCollectionInstance) return;

	FLinearColor Current = FLinearColor::Transparent;
	if (MaterialCollectionInstance->GetVectorParameterValue(ParameterName, Current))
	{
		MaterialCollectionInstance->SetVectorParameterValue(ParameterName, FMath::CInterpTo(Current, Target, Alpha, 1.0f));
	}
}



void AWeatherActor::BeginPlay()
{
	if (WeatherMaterialCollection)
	{
		MaterialCollectionInstance = GetWorld()->GetParameterCollectionInstance(WeatherMaterialCollection);
	}

	Super::BeginPlay();
}

void AWeatherActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

