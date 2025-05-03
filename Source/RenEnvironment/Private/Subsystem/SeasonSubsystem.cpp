// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Subsystem/SeasonSubsystem.h"

// Engine Header
#include "Kismet/KismetMaterialLibrary.h"
#include "Materials/MaterialParameterCollectionInstance.h"

// Project Header
#include "RenCore/Public/Asset/GameClockAsset.h"
#include "RenCore/Public/Developer/GameMetadataSettings.h"
#include "RenCore/Public/Timer/Timer.h"
#include "RenGlobal/Public/Macro/LogMacro.h"
#include "RenCore/Public/Priority/PrioritySystem.h"
#include "RenEnvironment/Public/Controller/WeatherController.h"
#include "RenEnvironment/Public/Asset/EnvironmentAsset.h"
#include "RenEnvironment/Public/Asset/WeatherAsset.h"
#include "RenEnvironment/Public/Asset/SeasonAsset.h"
#include "RenGameplay/Public/GameClockSubsystem.h"




void USeasonSubsystem::InitializeSeason()
{
	if (!IsValid(EnvironmentAsset))
	{
		LOG_ERROR(LogTemp, TEXT("EnvironmentAsset is invalid"));
		return;
	}

	if (!EnvironmentAsset->SeasonMaterialParameter)
	{
		LOG_ERROR(LogTemp, TEXT("Season MaterialParameters is invalid"));
		return;
	}

	SeasonCollectionInstance = GetWorld()->GetParameterCollectionInstance(EnvironmentAsset->SeasonMaterialParameter);
	if (!IsValid(SeasonCollectionInstance))
	{
		LOG_ERROR(LogTemp, TEXT("Season PrameterCollection is invalid"));
		return;
	}

}

void USeasonSubsystem::UpdateDay(int CurrentDay)
{
	if (!SeasonCollectionInstance || !IsValid(GameClockAsset))
	{
		PRINT_ERROR(LogTemp, 2.0f, TEXT("Season ParameterCollection or GameClockAsset is invalid"));
		return;
	}

	float Alpha = 0.0f, CurveAlpha = 0.0f;
	if (USeasonAsset* Season = GetSeasonAlpha(CurrentDay, GameClockAsset->TotalDaysInAYear, Alpha, CurveAlpha))
	{
		PRINT_WARNING(LogTemp, 1.0f, TEXT("Season: %s, Alpha: %f, CurveAlpha: %f"), *Season->SeasonName.ToString(), Alpha, CurveAlpha);

		SeasonCollectionInstance->SetScalarParameterValue("SeasonSpecular", FMath::Lerp(0.0f, Season->MaterialSpecular, CurveAlpha));
		SeasonCollectionInstance->SetScalarParameterValue("SeasonRoughness", FMath::Lerp(0.0f, Season->MaterialRoughness, CurveAlpha));
		SeasonCollectionInstance->SetScalarParameterValue("SeasonOpacity", FMath::Lerp(0.0f, Season->MaterialOpacity, CurveAlpha));
		SeasonCollectionInstance->SetVectorParameterValue("SeasonColor", FMath::CInterpTo(FLinearColor::Transparent, Season->MaterialColor, CurveAlpha, 1.0f));
	}
}



USeasonAsset* USeasonSubsystem::GetSeasonAlpha(int CurrentDay, int TotalDays, float& Alpha, float& CurveAlpha) const
{
	TArray<USeasonAsset*>& SeasonAssets = EnvironmentAsset->DefaultSeasons;

	int SeasonCount = SeasonAssets.Num();
	int ClampedDay = FMath::Clamp(CurrentDay, 1, TotalDays);

	for (int i = 0; i < SeasonCount; i++)
	{
		USeasonAsset* Season = SeasonAssets[i];

		if (ClampedDay >= Season->SeasonStartDay && ClampedDay <= Season->SeasonEndDay)
		{

			int DaySpan = Season->SeasonEndDay - Season->SeasonStartDay;
			if (DaySpan <= 0)
			{
				PRINT_ERROR(LogTemp, 2.0f, TEXT("Invalid season range"));

				Alpha = 0.0f;
				CurveAlpha = 0.0f;
				return Season;
			}

			Alpha = float(ClampedDay - Season->SeasonStartDay) / float(DaySpan);
			if (UCurveFloat* Curve = Season->SeasonCurve)
			{
				CurveAlpha = Curve->GetFloatValue(Alpha);
			}
			else
			{
				PRINT_ERROR(LogTemp, 2.0f, TEXT("Curve Asset is invalid, incorrect season transition is expected"));
				CurveAlpha = 0.0f;
			}

			return Season;
		}
	}

	Alpha = 0.0f;
	CurveAlpha = 0.0f;
	return nullptr;
}



bool USeasonSubsystem::IsSeasonsValid() const
{
	if (!IsValid(EnvironmentAsset) || !IsValid(GameClockAsset))
	{
		LOG_ERROR(LogTemp, TEXT("EnvironmentAsset or GameClockAsset is invalid"));
		return false;
	}


	TArray<USeasonAsset*>& SeasonAssets = EnvironmentAsset->DefaultSeasons;

	int SeasonCount = SeasonAssets.Num();
	if (SeasonCount == 0)
	{
		return false;
	}

	for (int i = 0; i < SeasonCount; i++)
	{
		USeasonAsset* Current = SeasonAssets[i];
		if (!IsValid(Current))
		{
			continue;
		}

		if (Current->SeasonStartDay > Current->SeasonEndDay)
		{
			LOG_ERROR(LogTemp, TEXT("Season's start day is greater than end day"));
			return false;
		}

		if (i > 0) {
			USeasonAsset* Previous = SeasonAssets[i - 1];
			if (Current->SeasonStartDay != Previous->SeasonEndDay + 1)
			{
				LOG_ERROR(LogTemp, TEXT("Invalid gap between seasons, %s"), *Previous->SeasonName.ToString());
				return false;
			}
		}

	}

	USeasonAsset* FirstSeason = SeasonAssets[0];
	USeasonAsset* LastSeason = SeasonAssets[SeasonCount - 1];
	if (FirstSeason->SeasonStartDay != 1 || LastSeason->SeasonEndDay != GameClockAsset->TotalDaysInAYear) {
		LOG_ERROR(LogTemp, TEXT("First season's start day is not 1 or last season's doesnt cover the whole year"));
		return false;
	}

	return true;
}






void USeasonSubsystem::HandleDayChange(int CurrentDay)
{
	UpdateDay(CurrentDay);
}



bool USeasonSubsystem::DoesSupportWorldType(EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

void USeasonSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	LOG_WARNING(LogTemp, TEXT("SeasonSubsystem initialized"));


	if (const UGameMetadataSettings* GameMetadata = GetDefault<UGameMetadataSettings>())
	{
		if (GameMetadata->ClockAsset.IsNull() || GameMetadata->EnvironmentAsset.IsNull())
		{
			PRINT_ERROR(LogTemp, 5.0f, TEXT("ClockAsset or EnvironmentAsset is not valid"));
			return;
		}

		GameClockAsset = Cast<UGameClockAsset>(GameMetadata->ClockAsset.LoadSynchronous());
		if (!IsValid(GameClockAsset))
		{
			PRINT_ERROR(LogTemp, 5.0f, TEXT("ClockAsset cast failed or is not valid"));
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

void USeasonSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	LOG_WARNING(LogTemp, TEXT("SeasonSubsystem begin play"));
}

void USeasonSubsystem::Deinitialize()
{
	if (IsValid(GameClockSubsystem))
	{
		GameClockSubsystem->OnDayChanged.RemoveAll(this);
	}

	LOG_WARNING(LogTemp, TEXT("SeasonSubsystem deinitialized"));
	Super::Deinitialize();
}

void USeasonSubsystem::PostInitialize()
{
	Super::PostInitialize();
	if (UWorld* World = GetWorld())
	{
		if (GameClockSubsystem = World->GetSubsystem<UGameClockSubsystem>())
		{
			GameClockSubsystem->OnDayChanged.AddDynamic(this, &USeasonSubsystem::HandleDayChange);
		}
	}
}

