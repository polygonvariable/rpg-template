// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Subsystem/EnvironmentSubsystem.h"

// Project Header
#include "RenCore/Public/Timer/Timer.h"
#include "RenGlobal/Public/Macro/LogMacro.h"

#include "Controller/EnvironmentProfile.h"
#include "Type/EnvironmentController.h"

#include "Components/ExponentialHeightFogComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SkyAtmosphereComponent.h"
#include "Components/SkyLightComponent.h"
#include "Components/StaticMeshComponent.h"



bool UEnvironmentSubsystem::AddEnvironmentController(const TEnumAsByte<EEnvironmentProfileType> ProfileType, TSubclassOf<UEnvironmentController> ControllerClass, const TMap<uint8, TWeakObjectPtr<USceneComponent>>& Components)
{
	if(EnvironmentControllers.Contains(ProfileType))
	{
		LOG_ERROR(this, LogTemp, "Environment Controller already exists");
		return false;
	}

	UEnvironmentController* Controller = NewObject<UEnvironmentController>(this, ControllerClass);
	if (!IsValid(Controller))
	{
		LOG_ERROR(this, LogTemp, "Failed to create Environment Controller");
		return false;
	}

	Controller->SetComponents(Components);
	EnvironmentControllers.Add(ProfileType, Controller);

	return true;
}

void UEnvironmentSubsystem::ValidateProfile(const TEnumAsByte<EEnvironmentProfileType> ProfileType, const FInstancedStruct Profile, TFunctionRef<void(UEnvironmentController* Controller, const FEnvironmentProfile* Profile)> Callback, const FString& LogMessage)
{
	if (!Profile.IsValid()) return;
	if (const FEnvironmentProfile* ResolvedProfile = Profile.GetPtr<FEnvironmentProfile>())
	{
		if (UEnvironmentController* Controller = EnvironmentControllers.FindRef(ProfileType))
		{
			Callback(Controller, ResolvedProfile);
			LOG_INFO(this, LogTemp, TEXT("%s"), *LogMessage);
		}
	}
}

void UEnvironmentSubsystem::AddEnvironmentProfile(const TEnumAsByte<EEnvironmentProfileType> ProfileType, FInstancedStruct Profile)
{
	ValidateProfile(ProfileType, Profile,
		[Profile](UEnvironmentController* InController, const FEnvironmentProfile* InProfile)
		{
			InController->AddItem(Profile, InProfile->Priority);
		},
		TEXT("Environment Profile added")
	);

	//if (!Profile.IsValid()) return;
	//
	//if (const FEnvironmentProfile* ResolvedProfile = Profile.GetPtr<FEnvironmentProfile>())
	//{
	//	UEnvironmentController* Controller = EnvironmentControllers.FindRef(ProfileType);
	//	if (IsValid(Controller))
	//	{
	//		LOG_INFO(this, LogTemp, "Environment Profile added");
	//		Controller->AddItem(Profile, ResolvedProfile->Priority);
	//	}
	//}
}

void UEnvironmentSubsystem::RemoveEnvironmentProfile(const TEnumAsByte<EEnvironmentProfileType> ProfileType, FInstancedStruct Profile)
{
	ValidateProfile(ProfileType, Profile,
		[](UEnvironmentController* InController, const FEnvironmentProfile* InProfile)
		{
			InController->RemoveItem(InProfile->Priority);
		},
		TEXT("Environment Profile removed")
	);
	//if (!Profile.IsValid()) return;

	//if (const FEnvironmentProfile* ResolvedProfile = Profile.GetPtr<FEnvironmentProfile>())
	//{
	//	UEnvironmentController* Controller = EnvironmentControllers.FindRef(ProfileType);
	//	if (IsValid(Controller))
	//	{
	//		LOG_INFO(this, LogTemp, "Environment Profile removed");
	//		Controller->RemoveItem(ResolvedProfile->Priority);
	//	}
	//}
}
