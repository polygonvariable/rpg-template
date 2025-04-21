// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "GameClockSubsystem.h"

// Project Headers
#include "RenCore/Public/Timer/Timer.h"
#include "RenGlobal/Public/Library/MiscLibrary.h"
#include "RenGlobal/Public/Macro/LogMacro.h"
#include "RenGlobal/Public/Record/ClockRecord.h"

#include "RenStorage/Public/Storage.h"
#include "RenStorage/Public/StorageSubsystem.h"


void UGameClockSubsystem::StartTimer()
{
	if(IsValid(ClockTimer))
	{
		LOG_WARNING(LogGameCycleSubsystem, TEXT("ClockTimer is already valid"));
		return;
	}

	ClockTimer = NewObject<UTimer>(this);
	if (!IsValid(ClockTimer))
	{
		LOG_ERROR(LogGameCycleSubsystem, TEXT("Failed to create ClockTimer"));
		return;
	}
	ClockTimer->OnTick.AddDynamic(this, &UGameClockSubsystem::HandleClockTick);
	ClockTimer->StartTimer(1.0f, 0);
}

void UGameClockSubsystem::StopTimer()
{
	if(!IsValid(ClockTimer))
	{
		LOG_ERROR(LogGameCycleSubsystem, TEXT("ClockTimer is not valid"));
		return;
	}
	ClockTimer->StopTimer();
}

float UGameClockSubsystem::GetTimeOfTheDay() const
{
	return TimeOfTheDay;
}

FString UGameClockSubsystem::GetFormattedTimeOfDay() const
{
	int32 TotalSeconds = FMath::FloorToInt(TimeOfTheDay);
	int32 Hours = TotalSeconds / 3600;
	int32 Minutes = (TotalSeconds % 3600) / 60;
	int32 Seconds = TotalSeconds % 60;

	return FString::Printf(TEXT("%02d:%02d:%02d"), Hours, Minutes, Seconds);
}

float UGameClockSubsystem::GetNormalizedTimeOfDay() const
{
	return FMath::Clamp(TimeOfTheDay / TotalSecondsInADay, 0.0f, 1.0f);
}

float UGameClockSubsystem::GetSmoothNormalizedTimeOfDay() const
{
	float CurrentSeconds = GetWorld()->GetTimeSeconds();
	float ElapsedSinceTick = CurrentSeconds - LastTickAt;
	float SmoothTime = TimeOfTheDay + ElapsedSinceTick;

	if (SmoothTime >= TotalSecondsInADay) SmoothTime -= TotalSecondsInADay;

	return FMath::Clamp(SmoothTime / TotalSecondsInADay, 0.0f, 1.0f);
}

float UGameClockSubsystem::GetRealTimeOfDay() const
{
	return FMath::GetMappedRangeValueClamped(TRange<float>(0.0f, TotalSecondsInADay), TRange<float>(0.0f, 24.0f), TimeOfTheDay);
}

bool UGameClockSubsystem::IsDay() const
{
	float RealHour = GetRealTimeOfDay();
	return RealHour >= 6.0f && RealHour < 18.0f;
}

bool UGameClockSubsystem::IsNight() const
{
	return !IsDay();
}

int UGameClockSubsystem::GetTotalDays() const
{
	return DayCounter;
}

void UGameClockSubsystem::RequestStorageUpdate()
{
	if (Storage.IsValid())
	{
		TMap<FName, FClockRecord>& Records = Storage->ClockRecords;
		if (FClockRecord* ClockRecord = Records.Find("DEFAULT"))
		{
			ClockRecord->Time = TimeOfTheDay;
			ClockRecord->DayCount = DayCounter;

			LOG_INFO(LogGameCycleSubsystem, TEXT("Clock day & time updated"));
		}
		else {
			Records.Add("DEFAULT", FClockRecord(TimeOfTheDay, DayCounter));
			LOG_INFO(LogGameCycleSubsystem, TEXT("Clock day & time added"));
		}
	}
	else
	{
		LOG_ERROR(LogGameCycleSubsystem, TEXT("Storage is not valid"));
	}
}

void UGameClockSubsystem::HandleClockTick(float CurrentTime)
{
	TimeOfTheDay += 1.0f;
	if (TimeOfTheDay >= TotalSecondsInADay)
	{
		TimeOfTheDay = 0.0f;
		DayCounter++;
		OnDayChanged.Broadcast(DayCounter);
	}

	LastTickAt = GetWorld()->GetTimeSeconds();
	OnTimeChanged.Broadcast(TimeOfTheDay);
}

void UGameClockSubsystem::LoadStoredTime()
{
	if (!Storage.IsValid())
	{
		LOG_ERROR(LogGameCycleSubsystem, TEXT("Storage is not valid"));
		return;
	}

	TMap<FName, FClockRecord>& Records = Storage->ClockRecords;
	if (FClockRecord* ClockRecord = Records.Find("DEFAULT"))
	{
		TimeOfTheDay = ClockRecord->Time;
		DayCounter = ClockRecord->DayCount;
		LOG_INFO(LogGameCycleSubsystem, TEXT("Clock day & time loaded"));
	}
	else {
		LOG_ERROR(LogGameCycleSubsystem, TEXT("Clock day & time not found"));
	}
}

void UGameClockSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	LOG_WARNING(LogGameCycleSubsystem, TEXT("ClockSubsystem initialized"));

	if (!OnWorldTearDownHandle.IsValid() && GetWorld()->IsGameWorld())
	{
		FWorldDelegates::OnWorldBeginTearDown.AddUObject(this, &UGameClockSubsystem::HandleWorldBeginTearDown);
	}

	if (UStorageSubsystem* StorageSubsystem = GetGameInstanceSubsystem<UStorageSubsystem>(GetWorld()))
	{
	 	Storage = StorageSubsystem->GetLocalStorage();
	 	LoadStoredTime();
	}
}

void UGameClockSubsystem::Deinitialize()
{
	if (OnWorldTearDownHandle.IsValid())
	{
		FWorldDelegates::OnWorldBeginTearDown.RemoveAll(this);
	}

	LOG_WARNING(LogGameCycleSubsystem, TEXT("ClockSubsystem deinitialized"));
	Super::Deinitialize();
}

void UGameClockSubsystem::HandleWorldBeginTearDown(UWorld* World)
{
	this->RequestStorageUpdate();
	if (UStorageSubsystem* StorageSubsystem = GetGameInstanceSubsystem<UStorageSubsystem>(World))
	{
		StorageSubsystem->UpdateStorage();
	}
}

