// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Controller/EnvironmentFogController.h"

// Engine Headers
#include "Components/ExponentialHeightFogComponent.h"

// Project Headers
#include "RenCore/Public/Timer/Timer.h"
#include "RenGlobal/Public/Macro/LogMacro.h"
#include "RenGlobal/Public/Library/MiscLibrary.h"

#include "RenEnvironment/Public/Asset/EnvironmentProfileAsset.h"
#include "RenEnvironment/Public/Profile/EnvironmentProfileType.h"



void UEnvironmentFogController::InitializeController()
{
	for (TObjectIterator<UExponentialHeightFogComponent> Itr; Itr; ++Itr)
	{
		if (!UMiscLibrary::IsInGameWorld(Itr->GetWorld())) continue;

		if (Itr->ComponentHasTag(ComponentName) && IsValid(*Itr))
		{
			FogComponent = *Itr;
			break;
		}
	}
}

void UEnvironmentFogController::HandleItemChanged(UObject* Item)
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

