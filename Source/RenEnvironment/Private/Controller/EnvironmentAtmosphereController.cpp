// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Controller/EnvironmentAtmosphereController.h"

// Engine Headers
#include "Components/SkyAtmosphereComponent.h"

// Project Headers
#include "RenCore/Public/Timer/Timer.h"
#include "RenGlobal/Public/Macro/LogMacro.h"
#include "RenEnvironment/Public/Asset/EnvironmentProfileAsset.h"
#include "RenEnvironment/Public/Profile/EnvironmentProfileType.h"



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

void UEnvironmentAtmosphereController::HandleTransitionTick(float CurrentTime)
{
	if (!Atmosphere.IsValid() || !ActiveProfile)
	{
		StopTransition();
		return;
	}

	float Alpha = TransitionTimer->GetNormalizedAlpha();
	float AScatter = Atmosphere->MieScatteringScale;
	float BScatter = ActiveProfile->MieScatteringScale;
	Atmosphere->SetMieScatteringScale(FMath::Lerp(AScatter, BScatter, Alpha));
}



UEnvironmentAtmosphereController2::UEnvironmentAtmosphereController2()
{
	ProfileType = EEnvironmentProfileType::Atmosphere;
}

void UEnvironmentAtmosphereController2::InitializeController()
{
	for (TObjectIterator<USkyAtmosphereComponent> Itr; Itr; ++Itr)
	{
		if (Itr->ComponentHasTag(ComponentName) && IsValid(*Itr))
		{
			AtmosphereComponent = *Itr;
			break;
		}
	}
}

void UEnvironmentAtmosphereController2::HandleItemChanged(UObject* Item)
{
	if (!AtmosphereComponent.IsValid())
	{
		LOG_ERROR(LogTemp, TEXT("AtmosphereComponent not found"));
		return;
	}

	UEnvironmentAtmosphereProfileAsset* AtmosphereProfile = Cast<UEnvironmentAtmosphereProfileAsset>(Item);
	if (!IsValid(AtmosphereProfile))
	{
		PRINT_ERROR(LogTemp, 2.0f, TEXT("AtmosphereProfile asset is invalid"));
		return;
	}

	AtmosphereComponent->SetMieScatteringScale(AtmosphereProfile->MieScatteringScale);
}

