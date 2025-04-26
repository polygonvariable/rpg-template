// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Controller/EnvironmentFogController.h"

// Engine Headers
#include "Components/ExponentialHeightFogComponent.h"

// Project Headers
#include "RenCore/Public/Timer/Timer.h"


void UEnvironmentFogController::SetComponents(const TMap<uint8, TWeakObjectPtr<USceneComponent>>& Components)
{
	if(Components.Num() == 0) return;
	if(!Components.FindRef(0).IsValid()) return;

	ExponentialHeightFog = Cast<UExponentialHeightFogComponent>(Components.FindRef(0).Get());
}

void UEnvironmentFogController::HandleItemChanged(const FInstancedStruct& Item)
{
	if (!ExponentialHeightFog.IsValid() || !ActiveItem.IsValid()) return;

	if (const FEnvironmentFogProfile* ResolvedProfile = ActiveItem.GetPtr<FEnvironmentFogProfile>())
	{
		ActiveProfile = ResolvedProfile;
		StartTransition();
	}
}

void UEnvironmentFogController::HandleTransitionTick(float CurrentTime)
{
	if (!ExponentialHeightFog.IsValid() || !ActiveProfile)
	{
		StopTransition();
		return;
	}

	float Alpha = TransitionTimer->GetNormalizedAlpha();
	float ADensity = ExponentialHeightFog->FogDensity;
	float BDensity = ActiveProfile->FogDensity;

	ExponentialHeightFog->SetFogDensity(FMath::Lerp(ADensity, BDensity, Alpha));
}

