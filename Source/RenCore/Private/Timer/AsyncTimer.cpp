// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Timer/AsyncTimer.h"

// Project Headers
#include "RenShared/Public/Macro/LogMacro.h"


UAsyncTimer* UAsyncTimer::Start(const UObject* InWorldContextObject, const float InTime, const bool bInLooping)
{
    UAsyncTimer* Task = NewObject<UAsyncTimer>();
    Task->Time = InTime;
	Task->bLooping = bInLooping;
	Task->WorldContextObject = InWorldContextObject;
    return Task;
}

void UAsyncTimer::Activate()
{
	if (UWorld* World = WorldContextObject->GetWorld())
	{
		FTimerManager& TimerManager = World->GetTimerManager();
		TimerManager.ClearTimer(TimerHandle);
		TimerManager.SetTimer(TimerHandle, this, &UAsyncTimer::HandleOnComplete, Time, FTimerManagerTimerParameters{ .bLoop = bLooping, .bMaxOncePerFrame = true });
		HandleOnStart();
	}
	else
	{
		LOG_ERROR(this, LogTemp, "World is not valid");
	}
}

void UAsyncTimer::HandleOnStart()
{
	OnStart.Broadcast();
}

void UAsyncTimer::HandleOnComplete()
{
	EndTask();
}

void UAsyncTimer::EndTask()
{
	if (UWorld* World = WorldContextObject->GetWorld())
	{
		World->GetTimerManager().ClearTimer(TimerHandle);
	}
	else
	{
		LOG_ERROR(this, LogTemp, "World is not valid");
	}

	OnComplete.Broadcast();

    if (IsValid(this))
    {
        SetReadyToDestroy();
        MarkAsGarbage();
    }
}