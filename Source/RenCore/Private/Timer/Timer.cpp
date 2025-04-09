// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Timer/Timer.h"
#include "RenGlobal/Public/Macro/LogMacro.h"


void UTimer::StartTimer_Implementation(const float InTime)
{
	if (InTime < 0.01f)
	{
		LOG_ERROR(this, LogTemp, "Timer time cannot be less than 0.01f");
		return;
	}

	bIsActive = true;
	DeltaTime = InTime;

	if (UWorld* World = GetWorld())
	{
		FTimerManager& TimerManager = World->GetTimerManager();
		TimerManager.ClearTimer(TimerHandle);
		TimerManager.SetTimer(TimerHandle, this, &UTimer::HandleTick, InTime, FTimerManagerTimerParameters{ .bLoop = bLooping, .bMaxOncePerFrame = true });
		OnStart.Broadcast();
	}
}

void UTimer::StopTimer_Implementation()
{
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(TimerHandle);
		bIsActive = false;
	}
	OnComplete.Broadcast();
}

void UTimer::RestartTimer_Implementation(const float InTime)
{
	StopTimer();
	StartTimer(InTime);
}


void UTimer::HandleTick_Implementation()
{
	DeltaTime += DeltaTime;
	OnTick.Broadcast();
	StopTimer();
}
