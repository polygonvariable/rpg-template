// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Region/RegionActor.h"

// Project Headers
#include "RenGlobal/Public/Library/MiscLibrary.h"
#include "RenGlobal/Public/Macro/LogMacro.h"

#include "Subsystem/EnvironmentSubsystem.h"


void ARegionActor::BeginPlay()
{
	if (UWorld* World = GetWorld())
	{
		EnvironmentSubsystem = World->GetSubsystem<UEnvironmentSubsystem>();
	}
	Super::BeginPlay();
}

void ARegionActor::HandlePlayerEntered()
{
	if (!IsValid(EnvironmentSubsystem))
	{
		LOG_ERROR(LogTemp, TEXT("EnvironmentSubsystem is not valid"));
		return;
	}

	for (const TPair<TEnumAsByte<EEnvironmentProfileType>, FInstancedStruct>& Profile : EnvironmentProfiles)
	{
		EnvironmentSubsystem->AddEnvironmentProfile(Profile.Key, Profile.Value);
	}
}

void ARegionActor::HandlePlayerExited()
{
	if (!IsValid(EnvironmentSubsystem))
	{
		LOG_ERROR(LogTemp, TEXT("EnvironmentSubsystem is not valid"));
		return;
	}

	for (const TPair<TEnumAsByte<EEnvironmentProfileType>, FInstancedStruct>& Profile : EnvironmentProfiles)
	{
		EnvironmentSubsystem->RemoveEnvironmentProfile(Profile.Key, Profile.Value);
	}
}

