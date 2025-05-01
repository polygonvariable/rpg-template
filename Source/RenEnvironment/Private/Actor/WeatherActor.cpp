// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Actor/WeatherActor.h"

// Engine Headers
#include "InstancedStruct.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Materials/MaterialParameterCollectionInstance.h"

// Project Header
#include "RenCore/Public/Priority/PrioritySystem.h"
#include "RenCore/Public/Timer/Timer.h"
#include "RenGlobal/Public/Macro/LogMacro.h"
#include "RenEnvironment/Public/Controller/WeatherController.h"



void AWeatherActor::SetWeather(FWeatherProfile Weather)
{
	if (WeatherController)
	{
		WeatherController->AddItem(FInstancedStruct::Make(Weather), Weather.Priority);
	}
}

void AWeatherActor::ResetWeather(FWeatherProfile Weather)
{
	if (WeatherController)
	{
		WeatherController->RemoveItem(Weather.Priority);
	}
}


void AWeatherActor::BeginPlay()
{
	if (WeatherMaterialCollection)
	{
		WeatherController = NewObject<UWeatherController>(this);
		if (WeatherController)
		{
			WeatherController->SetMaterialCollection(WeatherMaterialCollection);
		}
	}

	Super::BeginPlay();
}

void AWeatherActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

