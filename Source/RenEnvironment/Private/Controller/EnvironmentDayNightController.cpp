// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Controller/EnvironmentDayNightController.h"

// Engine Headers
#include "Components/DirectionalLightComponent.h"
#include "EngineUtils.h"

// Project Headers
#include "RenCore/Public/Timer/Timer.h"
#include "RenGlobal/Public/Macro/LogMacro.h"
#include "RenGlobal/Public/Library/MiscLibrary.h"
#include "RenGameplay/Public/GameClockSubsystem.h"

#include "RenEnvironment/Public/Component/OrbitalLightComponent.h"
#include "RenEnvironment/Public/Asset/EnvironmentProfileAsset.h"
#include "RenEnvironment/Public/Profile/EnvironmentProfileType.h"



void UEnvironmentDayNightController::StartDayTimer()
{
	if (!IsValid(DayTimer) || !SunComponent.IsValid() || !MoonComponent.IsValid() || !IsValid(GameClockSubsystem))
	{
		LOG_ERROR(LogTemp, "DayTimer, GameClockSubsystem, SunComponent or MoonComponent is not valid");
		return;
	}

	DayTimer->StartTimer(0.1f, 0);
}

void UEnvironmentDayNightController::StopDayTimer()
{
	if (!IsValid(DayTimer))
	{
		LOG_ERROR(LogTemp, "DayTimer is not valid");
		return;
	}

	DayTimer->StopTimer();
}

void UEnvironmentDayNightController::HandleDayTimerTick(float ElapsedTime)
{
	float NormalizedTime = GameClockSubsystem->GetSmoothNormalizedTime();
	float RealTime = NormalizedTime * 24.0f;

	SunComponent->SetTime(RealTime);
	MoonComponent->SetTime(RealTime);
}

void UEnvironmentDayNightController::InitializeController()
{
	bool bSunFound = false;
	bool bMoonFound = false;

	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (IsValid(*ActorItr) && ActorItr->ActorHasTag(ActorTag))
		{
			TArray<UActorComponent*> SunComponents = ActorItr->GetComponentsByTag(UOrbitalLightComponent::StaticClass(), SunComponentName);
			if (SunComponents.IsValidIndex(0) && IsValid(SunComponents[0]))
			{
				SunComponent = Cast<UOrbitalLightComponent>(SunComponents[0]);
				bSunFound = true;
			}

			TArray<UActorComponent*> MoonComponents = ActorItr->GetComponentsByTag(UOrbitalLightComponent::StaticClass(), MoonComponentName);
			if (MoonComponents.IsValidIndex(0) && IsValid(MoonComponents[0]))
			{
				MoonComponent = Cast<UOrbitalLightComponent>(MoonComponents[0]);
				bMoonFound = true;
			}

			break;
		}
	}

	if (!bSunFound || !bMoonFound)
	{
		LOG_ERROR(LogTemp, TEXT("Sun or Moon not found"));
		return;
	}


	if (!IsValid(DayTimer))
	{
		DayTimer = NewObject<UTimer>(this);
		if (!IsValid(DayTimer))
		{
			LOG_ERROR(LogTemp, "Failed to create DayTimer");
			return;
		}
		DayTimer->OnTick.AddDynamic(this, &UEnvironmentDayNightController::HandleDayTimerTick);
	}
	else
	{
		LOG_ERROR(LogTemp, "DayTimer is already valid");
	}


	if (UWorld* World = GetWorld())
	{
		GameClockSubsystem = World->GetSubsystem<UGameClockSubsystem>();
		if (!IsValid(GameClockSubsystem))
		{
			LOG_ERROR(LogTemp, TEXT("GameClockSubsystem is not valid"));
			return;
		}
		GameClockSubsystem->OnClockStarted.AddDynamic(this, &UEnvironmentDayNightController::StartDayTimer);
		GameClockSubsystem->OnClockStopped.AddDynamic(this, &UEnvironmentDayNightController::StopDayTimer);

		if (GameClockSubsystem->IsActive())
		{
			StartDayTimer();
		}
	}
	else
	{
		LOG_ERROR(LogTemp, TEXT("World is not valid"));
	}

}

void UEnvironmentDayNightController::CleanupController()
{
	if (IsValid(GameClockSubsystem))
	{
		GameClockSubsystem->OnClockStarted.RemoveAll(this);
		GameClockSubsystem->OnClockStopped.RemoveAll(this);
	}

	if (IsValid(DayTimer))
	{
		DayTimer->StopTimer();
		DayTimer->OnTick.RemoveAll(this);
		DayTimer->MarkAsGarbage();
	}

	DayTimer = nullptr;
	//SunComponent = nullptr;
	//MoonComponent = nullptr;
	GameClockSubsystem = nullptr;
}

