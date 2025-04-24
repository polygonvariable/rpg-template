// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Controller/EnvironmentLightController.h"

// Engine Headers
#include "Components/DirectionalLightComponent.h"

// Project Headers
#include "RenCore/Public/Timer/Timer.h"


void UEnvironmentLightController::SetComponents(const TMap<uint8, TWeakObjectPtr<USceneComponent>>& Components)
{
	if (Components.Num() == 0) return;
	if (!Components.FindRef(0).IsValid() || !Components.FindRef(1).IsValid()) return;

	Sun = Cast<UDirectionalLightComponent>(Components.FindRef(0).Get());
	Moon = Cast<UDirectionalLightComponent>(Components.FindRef(1).Get());
}

void UEnvironmentLightController::HandleItemChanged(const FInstancedStruct& Item)
{
	if (!Sun.IsValid() || !Moon.IsValid() || !ActiveItem.IsValid()) return;
	
	if (const FEnvironmentLightProfile* ResolvedProfile = ActiveItem.GetPtr<FEnvironmentLightProfile>())
	{
		ActiveProfile = ResolvedProfile;
		StartTransition();
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

