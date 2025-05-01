// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Subsystem/WeatherSubsystem.h"

// Engine Header
#include "Kismet/KismetMaterialLibrary.h"
#include "Materials/MaterialParameterCollectionInstance.h"

// Project Header
#include "RenGlobal/Public/Macro/LogMacro.h"
#include "RenCore/Public/Priority/PrioritySystem.h"



void UWeatherSubsystem::AddWeather(FWeatherProfile WeatherProfile)
{
	if (IsValid(WeatherPriority))
	{
		WeatherPriority->AddItem(FInstancedStruct::Make(WeatherProfile), WeatherProfile.Priority);
	}
}

void UWeatherSubsystem::RemoveWeather(FWeatherProfile WeatherProfile)
{
	if (IsValid(WeatherPriority))
	{
		WeatherPriority->RemoveItem(WeatherProfile.Priority);
	}
}



void UWeatherSubsystem::HandleWeatherChanged(const FInstancedStruct& Item)
{
	if (!Item.IsValid() || !MaterialCollectionInstance)
	{
		LOG_ERROR(LogTemp, TEXT("Item or MaterialCollection is invalid"));
		return;
	}

	if (const FWeatherProfile* WeatherProfile = Item.GetPtr<FWeatherProfile>())
	{
		HandleScalarTransition(TEXT("WeatherAlpha"), WeatherProfile->Alpha, 1.0f);
		HandleScalarTransition(TEXT("WeatherSpecular"), WeatherProfile->Specular, 1.0f);
		HandleScalarTransition(TEXT("WeatherRoughness"), WeatherProfile->Roughness, 1.0f);
		HandleScalarTransition(TEXT("WeatherOpacity"), WeatherProfile->Opacity, 1.0f);
		HandleColorTransition(TEXT("WeatherColor"), WeatherProfile->Color, 1.0f);
	}
}

void UWeatherSubsystem::HandleScalarTransition(FName ParameterName, float Target, float Alpha)
{
	if (!MaterialCollectionInstance) return;

	float Current = 0.0f;
	if (MaterialCollectionInstance->GetScalarParameterValue(ParameterName, Current))
	{
		MaterialCollectionInstance->SetScalarParameterValue(ParameterName, FMath::Lerp(Current, Target, Alpha));
	}
}

void UWeatherSubsystem::HandleColorTransition(FName ParameterName, const FLinearColor& Target, float Alpha)
{
	if (!MaterialCollectionInstance) return;

	FLinearColor Current = FLinearColor::Transparent;
	if (MaterialCollectionInstance->GetVectorParameterValue(ParameterName, Current))
	{
		MaterialCollectionInstance->SetVectorParameterValue(ParameterName, FMath::CInterpTo(Current, Target, Alpha, 1.0f));
	}
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
	LOG_WARNING(LogTemp, TEXT("WeatherSubsystem begin play"));

	WeatherPriority = NewObject<UPrioritySystem>(this);
	if (!IsValid(WeatherPriority))
	{
		LOG_ERROR(LogTemp, "Failed to create Weather Controller");
		return;
	}
	WeatherPriority->OnItemChanged.AddDynamic(this, &UWeatherSubsystem::HandleWeatherChanged);

	// MaterialCollectionInstance = GetWorld()->GetParameterCollectionInstance(MaterialCollection);
}

void UWeatherSubsystem::Deinitialize()
{
	if(IsValid(WeatherPriority))
	{
		WeatherPriority->OnItemChanged.RemoveAll(this);
		WeatherPriority->MarkAsGarbage();
	}

	LOG_WARNING(LogTemp, TEXT("WeatherSubsystem deinitialized"));
	Super::Deinitialize();
}

