// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Controller/EnvironmentAtmosphereController.h"

// Engine Headers
#include "Components/SkyAtmosphereComponent.h"

// Project Headers
#include "RenCore/Public/Timer/Timer.h"
#include "RenGlobal/Public/Macro/LogMacro.h"
#include "RenGlobal/Public/Library/MiscLibrary.h"

#include "RenEnvironment/Public/Asset/EnvironmentProfileAsset.h"
#include "RenEnvironment/Public/Profile/EnvironmentProfileType.h"



void UEnvironmentAtmosphereController::InitializeController()
{
	for (TObjectIterator<USkyAtmosphereComponent> Itr; Itr; ++Itr)
	{
		if (!UMiscLibrary::IsInGameWorld(Itr->GetWorld())) continue;

		if (Itr->ComponentHasTag(ComponentName) && IsValid(*Itr))
		{
			AtmosphereComponent = *Itr;
			break;
		}
	}
}

void UEnvironmentAtmosphereController::HandleItemChanged(UObject* Item)
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

