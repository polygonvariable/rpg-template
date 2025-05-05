// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Controller/EnvironmentFogController.h"

// Engine Headers
#include "Components/ExponentialHeightFogComponent.h"

// Project Headers
#include "RenCore/Public/Timer/Timer.h"
#include "RenGlobal/Public/Macro/LogMacro.h"

#include "RenEnvironment/Public/Asset/EnvironmentProfileAsset.h"
#include "RenEnvironment/Public/Profile/EnvironmentProfileType.h"



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



UEnvironmentFogController2::UEnvironmentFogController2()
{
	ProfileType = EEnvironmentProfileType::Fog;
}

void UEnvironmentFogController2::InitializeController()
{
	for (TObjectIterator<UExponentialHeightFogComponent> Itr; Itr; ++Itr)
	{
		if (Itr->ComponentHasTag(ComponentName) && IsValid(*Itr))
		{
			FogComponent = *Itr;
			break;
		}
	}
}

void UEnvironmentFogController2::HandleItemChanged(UObject* Item)
{
	if (!FogComponent.IsValid())
	{
		LOG_ERROR(LogTemp, TEXT("FogComponent not found"));
		return;
	}

	UEnvironmentFogProfileAsset* FogProfile = Cast<UEnvironmentFogProfileAsset>(Item);
	if (!IsValid(FogProfile))
	{
		PRINT_ERROR(LogTemp, 2.0f, TEXT("FogProfile asset is invalid"));
		return;
	}

	FogComponent->SetFogDensity(FogProfile->FogDensity);
}
