// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Controller/EnvironmentLightController.h"

// Engine Headers
#include "Components/DirectionalLightComponent.h"

// Project Headers
#include "RenCore/Public/Timer/Timer.h"
#include "RenGlobal/Public/Macro/LogMacro.h"
#include "RenGlobal/Public/Library/MiscLibrary.h"

#include "RenEnvironment/Public/Asset/EnvironmentProfileAsset.h"
#include "RenEnvironment/Public/Profile/EnvironmentProfileType.h"



void UEnvironmentLightController::InitializeController()
{
	bool bSunFound = false;
	bool bMoonFound = false;

	for (TObjectIterator<UDirectionalLightComponent> Itr; Itr; ++Itr)
	{
		if (!UMiscLibrary::IsInGameWorld(Itr->GetWorld())) continue;

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

	if (!bSunFound) LOG_ERROR(LogTemp, TEXT("Sun not found"));
	if (!bMoonFound) LOG_ERROR(LogTemp, TEXT("Moon not found"));
}

void UEnvironmentLightController::HandleItemChanged(UObject* Item)
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

