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


void UGameClockSubsystem::InitializeClock()
{
	if (IsValid(ClockTimer))
	{
		LOG_WARNING(LogClockSubsystem, TEXT("ClockTimer is already valid"));
		return;
	}

	ClockTimer = NewObject<UTimer>(this);
	if (!IsValid(ClockTimer))
	{
		LOG_ERROR(LogClockSubsystem, TEXT("Failed to create ClockTimer"));
		return;
	}

	ClockTimer->OnTick.AddDynamic(this, &UGameClockSubsystem::HandleClockTick);

	LOG_INFO(LogClockSubsystem, TEXT("ClockTimer created"));
}

void UGameClockSubsystem::CleanupClock()
{
	if (!IsValid(ClockTimer))
	{
		LOG_ERROR(LogClockSubsystem, TEXT("ClockTimer is not valid"));
		return;
	}

	ClockTimer->StopTimer(true);
	ClockTimer->OnTick.RemoveAll(this);
	ClockTimer->MarkAsGarbage();

	LOG_INFO(LogClockSubsystem, TEXT("ClockTimer removed"));
}

void UGameClockSubsystem::StartClock()
{
	if(!IsValid(ClockTimer))
	{
		LOG_ERROR(LogClockSubsystem, TEXT("ClockTimer is not valid"));
		return;
	}

	ClockTimer->StartTimer(1.0f, 0);
	OnClockStarted.Broadcast();
}

void UGameClockSubsystem::StopClock()
{
	if(!IsValid(ClockTimer))
	{
		LOG_ERROR(LogClockSubsystem, TEXT("ClockTimer is not valid"));
		return;
	}

	ClockTimer->StopTimer();
	OnClockStopped.Broadcast();
}

float UGameClockSubsystem::GetTimeOfTheDay() const
{
	return TimeOfTheDay;
}

FString UGameClockSubsystem::GetFormattedTimeOfDay(const FString& Format) const
{
	int32 TotalSeconds = FMath::FloorToInt(TimeOfTheDay);
	int32 Hours = TotalSeconds / 3600;
	int32 Minutes = (TotalSeconds % 3600) / 60;
	int32 Seconds = TotalSeconds % 60;
	
	FString AmPm = IsDay() ? TEXT("AM") : TEXT("PM");

	FString Result = Format;
	Result = Result.Replace(TEXT("hh"), *FString::Printf(TEXT("%02d"), Hours));
	Result = Result.Replace(TEXT("mm"), *FString::Printf(TEXT("%02d"), Minutes));
	Result = Result.Replace(TEXT("ss"), *FString::Printf(TEXT("%02d"), Seconds));
	Result = Result.Replace(TEXT("dd"), *FString::Printf(TEXT("%02d"), DayCount));
	Result = Result.Replace(TEXT("ap"), *AmPm);

	return Result;
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

float UGameClockSubsystem::GetSimulatedRealTimeOfDay() const
{
	return FMath::GetMappedRangeValueClamped(TRange<float>(0.0f, TotalSecondsInADay), TRange<float>(0.0f, 24.0f), TimeOfTheDay);
}


int UGameClockSubsystem::GetDay() const
{
	return DayCount;
}

bool UGameClockSubsystem::IsDay() const
{
	float RealHour = GetSimulatedRealTimeOfDay();
	return RealHour >= 6.0f && RealHour < 18.0f;
}

bool UGameClockSubsystem::IsNight() const
{
	return !IsDay();
}


void UGameClockSubsystem::LoadWorldTime()
{
	if (!Storage.IsValid())
	{
		LOG_ERROR(LogClockSubsystem, TEXT("Storage is not valid"));
		return;
	}

	TMap<FName, FClockRecord>& Records = Storage->ClockRecords;
	if (FClockRecord* ClockRecord = Records.Find("DEFAULT"))
	{
		TimeOfTheDay = ClockRecord->Time;
		DayCount = ClockRecord->DayCount;

		LOG_INFO(LogClockSubsystem, TEXT("Clock day & time loaded"));
	}
	else {
		LOG_ERROR(LogClockSubsystem, TEXT("Clock day & time not found"));
	}
}

void UGameClockSubsystem::SaveWorldTime()
{
	if (!Storage.IsValid())
	{
		LOG_ERROR(LogClockSubsystem, TEXT("Storage is not valid"));
		return;
	}

	TMap<FName, FClockRecord>& Records = Storage->ClockRecords;
	if (FClockRecord* ClockRecord = Records.Find("DEFAULT"))
	{
		ClockRecord->Time = TimeOfTheDay;
		ClockRecord->DayCount = DayCount;

		LOG_INFO(LogClockSubsystem, TEXT("Clock day & time updated"));
	}
	else {
		Records.Add("DEFAULT", FClockRecord(TimeOfTheDay, DayCount));

		LOG_INFO(LogClockSubsystem, TEXT("Clock day & time added"));
	}
}


void UGameClockSubsystem::HandleClockTick(float CurrentTime)
{
	TimeOfTheDay += 1.0f;
	if (TimeOfTheDay >= TotalSecondsInADay)
	{
		TimeOfTheDay = 0.0f;
		DayCount++;
		OnDayChanged.Broadcast(DayCount);
	}

	LastTickAt = GetWorld()->GetTimeSeconds();
	OnTimeChanged.Broadcast(TimeOfTheDay);
}

void UGameClockSubsystem::HandleWorldBeginTearDown(UWorld* World)
{
	SaveWorldTime();
}



bool UGameClockSubsystem::DoesSupportWorldType(EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

void UGameClockSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	LOG_WARNING(LogClockSubsystem, TEXT("ClockSubsystem initialized"));
}

void UGameClockSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	LOG_WARNING(LogClockSubsystem, TEXT("ClockSubsystem OnWorldBeginPlay"));

	if (!OnWorldBeginTearDownHandle.IsValid())
	{
		FWorldDelegates::OnWorldBeginTearDown.AddUObject(this, &UGameClockSubsystem::HandleWorldBeginTearDown);
	}

	if (UStorageSubsystem* StorageSubsystem = GetGameInstanceSubsystem<UStorageSubsystem>(GetWorld()))
	{
		Storage = StorageSubsystem->GetLocalStorage();
		LoadWorldTime();
	}

	InitializeClock();

	if (bAutoStart) {
		StartClock();
	}
}

void UGameClockSubsystem::Deinitialize()
{
	if (OnWorldBeginTearDownHandle.IsValid())
	{
		FWorldDelegates::OnWorldBeginTearDown.RemoveAll(this);
	}

	CleanupClock();

	LOG_WARNING(LogClockSubsystem, TEXT("ClockSubsystem deinitialized"));
	Super::Deinitialize();
}

