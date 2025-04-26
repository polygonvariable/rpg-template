// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Controller/EnvironmentController.h"

// Project Header
#include "RenGlobal/Public/Macro/LogMacro.h"
#include "RenCore/Public/Timer/Timer.h"


void UEnvironmentController::SetComponents(const TMap<uint8, TWeakObjectPtr<USceneComponent>>& Components)
{
}

void UEnvironmentController::StartTransition()
{
	if (!IsValid(TransitionTimer))
	{
		TransitionTimer = NewObject<UTimer>(this);
		if (!IsValid(TransitionTimer))
		{
			LOG_ERROR(LogTemp, "Failed to create timer");
			return;
		}
		TransitionTimer->OnTick.AddDynamic(this, &UEnvironmentController::HandleTransitionTick);
	}
	TransitionTimer->StartTimer(1.0f, 5, false);
}

void UEnvironmentController::StopTransition()
{
	if (IsValid(TransitionTimer)) TransitionTimer->StopTimer();
}

void UEnvironmentController::HandleTransitionTick(float CurrentTime)
{
}

void UEnvironmentController::BeginDestroy()
{
	if (IsValid(TransitionTimer))
	{
		TransitionTimer->StopTimer(true);
		TransitionTimer->MarkAsGarbage();
	}
	Super::BeginDestroy();
}

