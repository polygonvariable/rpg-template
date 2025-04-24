// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Controller/EnvironmentAtmosphereController.h"

// Engine Headers
#include "Components/SkyAtmosphereComponent.h"

// Project Headers
#include "RenCore/Public/Timer/Timer.h"


void UEnvironmentAtmosphereController::SetComponents(const TMap<uint8, TWeakObjectPtr<USceneComponent>>& Components)
{
	if (Components.Num() == 0) return;
	if (!Components.FindRef(0).IsValid()) return;
	Atmosphere = Cast<USkyAtmosphereComponent>(Components.FindRef(0).Get());
}

void UEnvironmentAtmosphereController::HandleItemChanged(const FInstancedStruct& Item)
{
	if (!Atmosphere.IsValid() || !ActiveItem.IsValid()) return;

	if (const FEnvironmentAtmosphereProfile* ResolvedProfile = ActiveItem.GetPtr<FEnvironmentAtmosphereProfile>())
	{
		ActiveProfile = ResolvedProfile;
		StartTransition();
	}
}

void UEnvironmentAtmosphereController::OnTransitioned(const float CurrentTime)
{
	if (!Atmosphere.IsValid() || !ActiveProfile)
	{
		TransitionTimer->StopTimer();
		return;
	}

	float Alpha = TransitionTimer->GetNormalizedAlpha();
	float AScatter = Atmosphere->MieScatteringScale;
	float BScatter = ActiveProfile->MieScatteringScale;
	Atmosphere->SetMieScatteringScale(FMath::Lerp(AScatter, BScatter, Alpha));
}

