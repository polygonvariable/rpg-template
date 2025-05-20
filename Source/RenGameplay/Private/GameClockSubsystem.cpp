// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "GameClockSubsystem.h"

// Engine Headers
#include "Kismet/GameplayStatics.h"

// Project Headers
#include "RenCore/Public/Developer/GameMetadataSettings.h"
#include "RenCore/Public/Timer/Timer.h"

#include "RenGlobal/Public/Library/MiscLibrary.h"
#include "RenGlobal/Public/Macro/LogMacro.h"
#include "RenGlobal/Public/Record/ClockRecord.h"

#include "RenAsset/Public/Game/GameClockAsset.h"

#include "RenStorage/Public/Storage.h"
#include "RenStorage/Public/StorageSubsystem.h"



bool UGameClockSubsystem::CreateClock()
{
	if (IsValid(ClockTimer))
	{
		LOG_WARNING(LogClockSubsystem, TEXT("ClockTimer is already valid"));
		return false;
	}

	ClockTimer = NewObject<UTimer>(this);
	if (!IsValid(ClockTimer))
	{
		LOG_ERROR(LogClockSubsystem, TEXT("Failed to create ClockTimer"));
		return false;
	}

	ClockTimer->OnTick.AddDynamic(this, &UGameClockSubsystem::HandleClockTick);

	LOG_INFO(LogClockSubsystem, TEXT("ClockTimer created"));

	return true;
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



UGameClockAsset* UGameClockSubsystem::GetClockAsset() const
{
	return ClockAsset;
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



float UGameClockSubsystem::GetCurrentTime() const
{
	return FMath::Clamp(CurrentTime, 0.0f, TotalSecondsInADay);
}

FString UGameClockSubsystem::GetFormattedTime(const FString& Format) const
{
	int32 TotalSeconds = FMath::FloorToInt(GetCurrentTime());
	int32 Hours = TotalSeconds / 3600;
	int32 Minutes = (TotalSeconds % 3600) / 60;
	int32 Seconds = TotalSeconds % 60;
	
	FString AmPm = IsDay() ? TEXT("AM") : TEXT("PM");

	FString Result = Format;
	Result = Result.Replace(TEXT("hh"), *FString::Printf(TEXT("%02d"), Hours));
	Result = Result.Replace(TEXT("mm"), *FString::Printf(TEXT("%02d"), Minutes));
	Result = Result.Replace(TEXT("ss"), *FString::Printf(TEXT("%02d"), Seconds));
	Result = Result.Replace(TEXT("dd"), *FString::Printf(TEXT("%02d"), GetCurrentDay()));
	Result = Result.Replace(TEXT("ap"), *AmPm);

	return Result;
}

float UGameClockSubsystem::GetNormalizedTime() const
{
	return FMath::Clamp(GetCurrentTime() / TotalSecondsInADay, 0.0f, 1.0f);
}

float UGameClockSubsystem::GetSmoothNormalizedTime() const
{
	float CurrentSeconds = GetWorld()->GetTimeSeconds();
	float ElapsedSinceTick = CurrentSeconds - LastTickAt;
	float SmoothTime = GetCurrentTime() + ElapsedSinceTick;

	if (SmoothTime >= TotalSecondsInADay) SmoothTime -= TotalSecondsInADay;

	return FMath::Clamp(SmoothTime / TotalSecondsInADay, 0.0f, 1.0f);
}

float UGameClockSubsystem::GetSimulatedRealTime() const
{
	return FMath::GetMappedRangeValueClamped(TRange<float>(0.0f, TotalSecondsInADay), TRange<float>(0.0f, 24.0f), GetCurrentTime());
}


int UGameClockSubsystem::GetCurrentDay() const
{
	return FMath::Clamp(CurrentDay, 1, TotalDaysInAYear);
}

bool UGameClockSubsystem::IsDay() const
{
	float RealHour = GetSimulatedRealTime();
	return RealHour >= 6.0f && RealHour < 18.0f;
}

bool UGameClockSubsystem::IsNight() const
{
	return !IsDay();
}

bool UGameClockSubsystem::IsActive() const
{
	return IsValid(ClockTimer) && ClockTimer->IsActive();
}


void UGameClockSubsystem::LoadWorldTime()
{
	if (!Storage.IsValid())
	{
		LOG_ERROR(LogClockSubsystem, TEXT("Storage is not valid"));
		return;
	}

	FName MapName = FName(GetWorld()->GetMapName());

	TMap<FName, FClockRecord>& Records = Storage->ClockRecords;
	if (FClockRecord* ClockRecord = Records.Find(MapName))
	{
		CurrentTime = FMath::Clamp(ClockRecord->Time, 0.0f, TotalSecondsInADay);
		CurrentDay = FMath::Clamp(ClockRecord->DayCount, 1, TotalDaysInAYear);

		OnDayChanged.Broadcast(CurrentDay);
		OnTimeChanged.Broadcast(CurrentTime);

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

	FName MapName = FName(GetWorld()->GetMapName());

	TMap<FName, FClockRecord>& Records = Storage->ClockRecords;
	if (FClockRecord* ClockRecord = Records.Find(MapName))
	{
		ClockRecord->Time = GetCurrentTime();
		ClockRecord->DayCount = GetCurrentDay();

		LOG_INFO(LogClockSubsystem, TEXT("Clock day & time updated"));
	}
	else {
		Records.Add("DEFAULT", FClockRecord(GetCurrentTime(), GetCurrentDay()));

		LOG_INFO(LogClockSubsystem, TEXT("Clock day & time added"));
	}
}


void UGameClockSubsystem::HandleClockTick(float ElapsedTime)
{
	CurrentTime += 1.0f;
	if (CurrentTime >= TotalSecondsInADay)
	{
		CurrentTime = 0.0f;

		CurrentDay++;
		if (CurrentDay > TotalDaysInAYear)
		{
			CurrentDay = 1;
		}

		OnDayChanged.Broadcast(CurrentDay);
	}

	LastTickAt = GetWorld()->GetTimeSeconds();
	OnTimeChanged.Broadcast(CurrentTime);
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


	if (const UGameMetadataSettings* GameMetadata = GetDefault<UGameMetadataSettings>())
	{
		if (GameMetadata->ClockAsset.IsNull())
		{
			LOG_ERROR(LogClockSubsystem, TEXT("ClockAsset is not valid"));
			return;
		}

		ClockAsset = Cast<UGameClockAsset>(GameMetadata->ClockAsset.LoadSynchronous());
		if (!IsValid(ClockAsset))
		{
			LOG_ERROR(LogClockSubsystem, TEXT("ClockAsset cast failed or is not valid"));
			return;
		}

		TotalSecondsInADay = ClockAsset->TotalSecondsInADay;
		TotalDaysInAYear = ClockAsset->TotalDaysInAYear;
	}

}

void UGameClockSubsystem::OnWorldComponentsUpdated(UWorld& InWorld)
{
	Super::OnWorldComponentsUpdated(InWorld);
	LOG_WARNING(LogClockSubsystem, TEXT("ClockSubsystem OnWorldComponentsUpdated"));

	if (!OnWorldBeginTearDownHandle.IsValid())
	{
		FWorldDelegates::OnWorldBeginTearDown.AddUObject(this, &UGameClockSubsystem::HandleWorldBeginTearDown);
	}

	if (UStorageSubsystem* StorageSubsystem = GetGameInstanceSubsystem<UStorageSubsystem>(GetWorld()))
	{
		Storage = StorageSubsystem->GetLocalStorage();
		LoadWorldTime();
	}

	if (CreateClock() && bAutoStart) {
		StartClock();
	}
}

void UGameClockSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	LOG_WARNING(LogClockSubsystem, TEXT("ClockSubsystem OnWorldBeginPlay"));
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

