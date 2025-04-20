// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Timer/Timer.h"
#include "RenGlobal/Public/Macro/LogMacro.h"


void UTimer::StartTimer_Implementation(const float InTickInterval, const int InTickLimit, const bool bPreserveTime)
{
	if (InTickInterval < 0.001f)
	{
		LOG_ERROR(this, LogTemp, "Timer time cannot be less than 0.001f");
		return;
	}

	TickLimit = InTickLimit;
	TickInterval = InTickInterval;

	if (!bPreserveTime)
	{
		Time = 0.0f;
		TickCount = 0;
	}

	if (UWorld* World = GetWorld())
	{
		FTimerManager& TimerManager = World->GetTimerManager();
		TimerManager.ClearTimer(TimerHandle);

		//bool bShouldLoop = TickLimit <= 0;
		bool bShouldLoop = true;
		TimerManager.SetTimer(TimerHandle, this, &UTimer::HandleTick, TickInterval, FTimerManagerTimerParameters{ .bLoop = bShouldLoop, .bMaxOncePerFrame = true });
		
		OnStarted.Broadcast();
	}
}


void UTimer::StopTimer_Implementation()
{
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(TimerHandle);

		Time = 0.0f;
		TickCount = 0;

		OnCompleted.Broadcast();
	}
}


void UTimer::RestartTimer_Implementation(const float InTickInterval, const int InTickLimit)
{
	StopTimer();
	StartTimer(InTickInterval, InTickLimit, false);
}


void UTimer::SetTickInterval_Implementation(const float InTickInterval)
{
	StopTimer();
	StartTimer(InTickInterval, TickLimit, true);
}


const bool UTimer::bIsActive_Implementation()
{
	if (UWorld* World = GetWorld())
	{
		return World->GetTimerManager().IsTimerActive(TimerHandle);
	}
	return false;
}


const float UTimer::GetNormalizedAlpha_Implementation()
{
	if (TickLimit <= 0 || TickInterval <= 0.0f)
	{
		return 0.0f;
	}
	const float TotalTime = TickLimit * TickInterval;
	return FMath::Clamp(Time / TotalTime, 0.0f, 1.0f);
}

void UTimer::HandleTick_Implementation()
{
	Time += TickInterval;
	TickCount++;

	OnTick.Broadcast(Time, TickLimit * TickInterval);

	if (TickLimit > 0 && TickCount >= TickLimit)
	{
		StopTimer();
	}
}
