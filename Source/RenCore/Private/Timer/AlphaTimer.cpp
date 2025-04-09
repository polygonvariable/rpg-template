// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Timer/AlphaTimer.h"


UAlphaTimer::UAlphaTimer()
{
	bLooping = true;
}

void UAlphaTimer::StartTimer_Implementation(const float InTime)
{
	TickIncrement = 0;
	TickLimit = InTime / TickFrequency;
	Super::StartTimer_Implementation(TickFrequency);
}

void UAlphaTimer::HandleTick_Implementation()
{
	if (TickIncrement >= TickLimit)
	{
		StopTimer();
		return;
	}
	
	float Alpha = (float)TickIncrement / (float)TickLimit;
	TickIncrement++;

	OnAlphaTick.Broadcast(Alpha);
}
