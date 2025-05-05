// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Controller/EnvironmentLightController.h"

// Engine Headers
#include "Components/DirectionalLightComponent.h"

// Project Headers
#include "RenCore/Public/Timer/Timer.h"
#include "RenGlobal/Public/Macro/LogMacro.h"

#include "RenEnvironment/Public/Asset/EnvironmentProfileAsset.h"
#include "RenEnvironment/Public/Profile/EnvironmentProfileType.h"



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

void UEnvironmentLightController::HandleTransitionTick(float CurrentTime)
{
	if (!Sun.IsValid() || !Moon.IsValid() || !ActiveProfile)
	{
		StopTransition();
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



UEnvironmentLightController2::UEnvironmentLightController2()
{
	ProfileType = EEnvironmentProfileType::Light;
}

void UEnvironmentLightController2::InitializeController()
{
	bool bSunFound = false;
	bool bMoonFound = false;

	for (TObjectIterator<UDirectionalLightComponent> Itr; Itr; ++Itr)
	{
		if (Itr->ComponentHasTag(SunComponentName) && IsValid(*Itr))
		{
			SunComponent = *Itr;
			bSunFound = true;
		}
		if (Itr->ComponentHasTag(MoonComponentName) && IsValid(*Itr))
		{
			MoonComponent = *Itr;
			bMoonFound = true;
		}
		if(bSunFound && bMoonFound) break;
	}

	if (!bSunFound) PRINT_ERROR(LogTemp, 2.0f, TEXT("Sun not found"));
	if (!bMoonFound) PRINT_ERROR(LogTemp, 2.0f, TEXT("Moon not found"));
}

void UEnvironmentLightController2::HandleItemChanged(UObject* Item)
{
	if (!SunComponent.IsValid() || !MoonComponent.IsValid())
	{
		LOG_ERROR(LogTemp, TEXT("Sun or Moon not found"));
		return;
	}

	UEnvironmentLightProfileAsset* LightProfile = Cast<UEnvironmentLightProfileAsset>(Item);
	if (!IsValid(LightProfile))
	{
		PRINT_ERROR(LogTemp, 2.0f, TEXT("LightProfile asset is invalid"));
		return;
	}

	SunComponent->SetIntensity(LightProfile->SunIntensity);
	SunComponent->SetLightColor(LightProfile->SunColor);
	MoonComponent->SetIntensity(LightProfile->MoonIntensity);
	MoonComponent->SetLightColor(LightProfile->MoonColor);
}

