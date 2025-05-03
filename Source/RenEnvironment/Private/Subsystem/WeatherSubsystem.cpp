// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Subsystem/WeatherSubsystem.h"

// Engine Header
#include "Kismet/KismetMaterialLibrary.h"
#include "Materials/MaterialParameterCollectionInstance.h"

// Project Header
#include "RenCore/Public/Developer/GameMetadataSettings.h"
#include "RenCore/Public/Timer/Timer.h"
#include "RenGlobal/Public/Macro/LogMacro.h"
#include "RenCore/Public/Priority/PrioritySystem.h"

#include "RenEnvironment/Public/Controller/WeatherController.h"
#include "RenEnvironment/Public/Asset/WeatherAsset.h"
#include "RenEnvironment/Public/Asset/EnvironmentAsset.h"



void UWeatherSubsystem::AddWeather(UWeatherAsset* WeatherAsset, int Priority)
{
	if (IsValid(WeatherController) && IsValid(WeatherAsset))
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



void UWeatherSubsystem::CreateWeatherTimer()
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

	WeatherTimer->StartTimer(5.0f, 0, false);
}

void UWeatherSubsystem::HandleWeatherTimer(float ElapsedTime)
{
	PRINT_WARNING(LogTemp, 1.0f, TEXT("Weather can change"));
	OnWeatherCanChange.Broadcast();
}

bool UWeatherSubsystem::CreateWeatherController()
{
	if (IsValid(WeatherController))
	{
		LOG_WARNING(LogTemp, "Weather Controller is already valid");
		return false;
	}

	WeatherController = NewObject<UWeatherController>(this);
	if (!IsValid(WeatherController))
	{
		LOG_ERROR(LogTemp, "Failed to create Weather Controller");
		return false;
	}

	return true;
}

void UWeatherSubsystem::CreateWeatherMaterialCollection()
{
	if (!IsValid(EnvironmentAsset) || !IsValid(WeatherController))
	{
		LOG_ERROR(LogTemp, TEXT("EnvironmentAsset or WeatherController is invalid"));
		return;
	}
	WeatherController->SetMaterialCollection(EnvironmentAsset->WeatherMaterialParameter);
}




bool UWeatherSubsystem::DoesSupportWorldType(EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

void UWeatherSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	LOG_WARNING(LogTemp, TEXT("WeatherSubsystem initialized"));


	if (const UGameMetadataSettings* GameMetadata = GetDefault<UGameMetadataSettings>())
	{
		if (GameMetadata->EnvironmentAsset.IsNull())
		{
			PRINT_ERROR(LogTemp, 5.0f, TEXT("ClockAsset or EnvironmentAsset is not valid"));
			return;
		}

		EnvironmentAsset = Cast<UEnvironmentAsset>(GameMetadata->EnvironmentAsset.LoadSynchronous());
		if (!IsValid(EnvironmentAsset))
		{
			PRINT_ERROR(LogTemp, 5.0f, TEXT("Environment cast failed or is not valid"));
			return;
		}
	}
}

void UWeatherSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	LOG_WARNING(LogTemp, TEXT("WeatherSubsystem begin play"));

	if (CreateWeatherController())
	{
		CreateWeatherTimer();
		CreateWeatherMaterialCollection();
	}
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

