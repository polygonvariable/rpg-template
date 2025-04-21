// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Type/EnvironmentController.h"

// Engine Header
#include "Math/UnrealMathUtility.h"
#include "Math/Color.h"

// Project Header
#include "RenGlobal/Public/Macro/LogMacro.h"
#include "RenCore/Public/Timer/Timer.h"


void UEnvironmentController::SetComponents(const TMap<uint8, TWeakObjectPtr<USceneComponent>>& Components)
{
}

void UEnvironmentController::SetTimer()
{
	if (!IsValid(TransitionTimer))
	{
		TransitionTimer = NewObject<UTimer>(this);
		if (!IsValid(TransitionTimer))
		{
			LOG_ERROR(LogTemp, "Failed to create timer");
			return;
		}
		TransitionTimer->OnTick.AddDynamic(this, &UEnvironmentController::OnTransitioned);
	}
	TransitionTimer->StartTimer(1.0f, 5, false);
}

void UEnvironmentController::OnTransitioned(const float CurrentTime)
{
}


void UEnvironmentFogController::SetComponents(const TMap<uint8, TWeakObjectPtr<USceneComponent>>& Components)
{
	if(Components.Num() == 0) return;
	if(!Components.FindRef(0).IsValid()) return;

	ExponentialHeightFog = Cast<UExponentialHeightFogComponent>(Components.FindRef(0).Get());
}

void UEnvironmentFogController::OnActiveItemChanged_Implementation()
{
	if (!ExponentialHeightFog.IsValid() || !ActiveItem.IsValid()) return;

	if (const FEnvironmentFogProfile* ResolvedProfile = ActiveItem.GetPtr<FEnvironmentFogProfile>())
	{
		ActiveProfile = ResolvedProfile;
		SetTimer();
	}
}

void UEnvironmentFogController::OnTransitioned(const float CurrentTime)
{
	if (!ExponentialHeightFog.IsValid() || !ActiveProfile)
	{
		TransitionTimer->StopTimer();
		return;
	}

	float Alpha = TransitionTimer->GetNormalizedAlpha();
	float ADensity = ExponentialHeightFog->FogDensity;
	float BDensity = ActiveProfile->FogDensity;

	ExponentialHeightFog->SetFogDensity(FMath::Lerp(ADensity, BDensity, Alpha));
}


void UEnvironmentLightController::SetComponents(const TMap<uint8, TWeakObjectPtr<USceneComponent>>& Components)
{
	if (Components.Num() == 0) return;
	if (!Components.FindRef(0).IsValid() || !Components.FindRef(1).IsValid()) return;

	Sun = Cast<UDirectionalLightComponent>(Components.FindRef(0).Get());
	Moon = Cast<UDirectionalLightComponent>(Components.FindRef(1).Get());
}

void UEnvironmentLightController::OnActiveItemChanged_Implementation()
{
	if (!Sun.IsValid() || !Moon.IsValid() || !ActiveItem.IsValid()) return;
	
	if (const FEnvironmentLightProfile* ResolvedProfile = ActiveItem.GetPtr<FEnvironmentLightProfile>())
	{
		ActiveProfile = ResolvedProfile;
		SetTimer();
	}
}

void UEnvironmentLightController::OnTransitioned(const float CurrentTime)
{
	if (!Sun.IsValid() || !Moon.IsValid() || !ActiveProfile)
	{
		TransitionTimer->StopTimer();
		return;
	}

	float Alpha = TransitionTimer->GetNormalizedAlpha();
	float ASunIntensity = Sun->Intensity;
	float BSunIntensity = ActiveProfile->SunIntensity;
	FColor ASunColor = Sun->LightColor;
	FColor BSunColor = ActiveProfile->SunColor;

	Sun->SetIntensity(FMath::Lerp(ASunIntensity, BSunIntensity, Alpha));
	Sun->SetLightColor(FMath::CInterpTo(ASunColor, BSunColor, Alpha, 1.0f).ToFColor(false));

	float AMoonIntensity = Moon->Intensity;
	float BMoonIntensity = ActiveProfile->MoonIntensity;
	FColor AMoonColor = Moon->LightColor;
	FColor BMoonColor = ActiveProfile->MoonColor;

	Moon->SetIntensity(FMath::Lerp(AMoonIntensity, BMoonIntensity, Alpha));
	Moon->SetLightColor(FMath::CInterpTo(AMoonColor, BMoonColor, Alpha, 1.0f).ToFColor(false));
}


void UEnvironmentAtmosphereController::SetComponents(const TMap<uint8, TWeakObjectPtr<USceneComponent>>& Components)
{
	if (Components.Num() == 0) return;
	if (!Components.FindRef(0).IsValid()) return;
	Atmosphere = Cast<USkyAtmosphereComponent>(Components.FindRef(0).Get());
}

void UEnvironmentAtmosphereController::OnActiveItemChanged_Implementation()
{
	if (!Atmosphere.IsValid() || !ActiveItem.IsValid() || !ActiveProfile) return;

	if (const FEnvironmentAtmosphereProfile* ResolvedProfile = ActiveItem.GetPtr<FEnvironmentAtmosphereProfile>())
	{
		ActiveProfile = ResolvedProfile;
		SetTimer();
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
