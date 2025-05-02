// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Subsystem/WeatherSubsystem.h"

// Engine Header
#include "Kismet/KismetMaterialLibrary.h"
#include "Materials/MaterialParameterCollectionInstance.h"

// Project Header
#include "RenCore/Public/Timer/Timer.h"
#include "RenGlobal/Public/Macro/LogMacro.h"
#include "RenCore/Public/Priority/PrioritySystem.h"
#include "RenEnvironment/Public/Controller/WeatherController.h"
#include "RenEnvironment/Public/Asset/WeatherAsset.h"



void UWeatherSubsystem::SetMaterialCollection(UMaterialParameterCollection* MaterialCollection)
{
	if (!MaterialCollection || !IsValid(WeatherController))
	{
		LOG_ERROR(LogTemp, TEXT("MaterialCollection or WeatherController is invalid"));
		return;
	}
	WeatherController->SetMaterialCollection(MaterialCollection);
}



void UWeatherSubsystem::AddWeather(UWeatherAsset* WeatherAsset, int Priority)
{
	if (IsValid(WeatherController))
	{
		WeatherController->AddItem(WeatherAsset, Priority);
	}
}

void UWeatherSubsystem::RemoveWeather(int Priority)
{
	if (IsValid(WeatherController))
	{
		WeatherController->RemoveItem(Priority);
	}
}



void UWeatherSubsystem::InitializeWeatherTimer(bool bAutoStart)
{
	if (!IsValid(WeatherTimer))
	{
		WeatherTimer = NewObject<UTimer>(this);
		if (!IsValid(WeatherTimer))
		{
			LOG_ERROR(LogTemp, "Failed to create weather timer");
			return;
		}
		WeatherTimer->OnTick.AddDynamic(this, &UWeatherSubsystem::HandleWeatherTimer);
	}

	if (bAutoStart) WeatherTimer->StartTimer(5.0f, 0, false);
}

void UWeatherSubsystem::HandleWeatherTimer(float CurrentTime)
{
	PRINT_WARNING(LogTemp, 1.0f, TEXT("Weather can change"));
	OnWeatherCanChange.Broadcast();
}



bool UWeatherSubsystem::DoesSupportWorldType(EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

void UWeatherSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	LOG_WARNING(LogTemp, TEXT("WeatherSubsystem initialized"));
}

void UWeatherSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	LOG_WARNING(LogTemp, TEXT("WeatherSubsystem begin play"));

	WeatherController = NewObject<UWeatherController>(this);
	if (!IsValid(WeatherController))
	{
		LOG_ERROR(LogTemp, "Failed to create Weather Controller");
		return;
	}

	InitializeWeatherTimer(true);
}

void UWeatherSubsystem::Deinitialize()
{
	if (IsValid(WeatherController))
	{
		WeatherController->MarkAsGarbage();
	}

	if (IsValid(WeatherTimer))
	{
		WeatherTimer->StopTimer(false);
		WeatherTimer->OnTick.RemoveAll(this);
		WeatherTimer->MarkAsGarbage();
	}

	LOG_WARNING(LogTemp, TEXT("WeatherSubsystem deinitialized"));
	Super::Deinitialize();
}

