// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Timer/AsyncAlphaTimer.h"

// Project Headers
#include "RenGlobal/Public/Macro/LogMacro.h"


UAsyncAlphaTimer* UAsyncAlphaTimer::Start(const UObject* InWorldContextObject, const float InTime, const float InTickFrequency)
{
    UAsyncAlphaTimer* Task = NewObject<UAsyncAlphaTimer>();
    Task->Time = FMath::Max(InTime, 0.01f);
	Task->TickFrequency = FMath::Max(InTickFrequency, 0.01f);
	Task->WorldContextObject = InWorldContextObject;
    return Task;
}

void UAsyncAlphaTimer::Activate()
{
	if (UWorld* World = WorldContextObject->GetWorld())
	{
		TickIncrement = 0;
		TickLimit = Time / TickFrequency;

		FTimerManager& TimerManager = World->GetTimerManager();
		TimerManager.ClearTimer(TimerHandle);
		TimerManager.SetTimer(TimerHandle, this, &UAsyncAlphaTimer::HandleOnTick, TickFrequency, FTimerManagerTimerParameters{ .bLoop = true, .bMaxOncePerFrame = true });
		HandleOnStart();
	}
	else
	{
		LOG_ERROR(this, LogTemp, "World is not valid");
		EndTask();
	}
}

void UAsyncAlphaTimer::HandleOnStart()
{
	OnStart.Broadcast(0.0f);
}

void UAsyncAlphaTimer::HandleOnTick()
{
	if (TickIncrement >= TickLimit)
	{
		HandleOnComplete();
		return;
	}
	
	float Alpha = (float)TickIncrement / (float)TickLimit;
	TickIncrement++;

	OnTick.Broadcast(Alpha);
}

void UAsyncAlphaTimer::HandleOnComplete()
{
	EndTask();
}

void UAsyncAlphaTimer::EndTask()
{
	if (UWorld* World = WorldContextObject->GetWorld())
	{
		World->GetTimerManager().ClearTimer(TimerHandle);
	}
	else
	{
		LOG_ERROR(this, LogTemp, "World is not valid");
	}

	OnComplete.Broadcast(1.0f);

    if (IsValid(this))
    {
        SetReadyToDestroy();
        MarkAsGarbage();
    }
}