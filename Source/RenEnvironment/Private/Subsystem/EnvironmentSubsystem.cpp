// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Subsystem/EnvironmentSubsystem.h"

// Engine Header
#include "Components/SceneComponent.h"

// Project Header
#include "RenGlobal/Public/Macro/LogMacro.h"

#include "Profile/EnvironmentProfile.h"
#include "Controller/EnvironmentController.h"




bool UEnvironmentSubsystem::AddEnvironmentController(const TEnumAsByte<EEnvironmentProfileType> ProfileType, TSubclassOf<UEnvironmentController> ControllerClass, const TMap<uint8, TWeakObjectPtr<USceneComponent>>& Components)
{
	if(EnvironmentControllers.Contains(ProfileType))
	{
		LOG_ERROR(LogTemp, "Environment Controller already exists");
		return false;
	}

	UEnvironmentController* Controller = NewObject<UEnvironmentController>(this, ControllerClass);
	if (!IsValid(Controller))
	{
		LOG_ERROR(LogTemp, "Failed to create Environment Controller");
		return false;
	}

	Controller->SetComponents(Components);
	EnvironmentControllers.Add(ProfileType, Controller);

	return true;
}

void UEnvironmentSubsystem::ValidateEnvironmentProfile(const TEnumAsByte<EEnvironmentProfileType> ProfileType, const FInstancedStruct Profile, TFunctionRef<void(UEnvironmentController* Controller, const FEnvironmentProfile* Profile)> Callback, const FString& LogMessage)
{
	if (!Profile.IsValid()) return;
	if (const FEnvironmentProfile* ResolvedProfile = Profile.GetPtr<FEnvironmentProfile>())
	{
		if (UEnvironmentController* Controller = EnvironmentControllers.FindRef(ProfileType))
		{
			Callback(Controller, ResolvedProfile);
			LOG_INFO(LogTemp, TEXT("%s"), *LogMessage);
		}
	}
}

void UEnvironmentSubsystem::AddEnvironmentProfile(const TEnumAsByte<EEnvironmentProfileType> ProfileType, FInstancedStruct Profile)
{
	ValidateEnvironmentProfile(ProfileType, Profile,
		[Profile](UEnvironmentController* InController, const FEnvironmentProfile* InProfile)
		{
			InController->AddItem(Profile, InProfile->Priority);
		},
		TEXT("Environment Profile added")
	);
}

void UEnvironmentSubsystem::RemoveEnvironmentProfile(const TEnumAsByte<EEnvironmentProfileType> ProfileType, FInstancedStruct Profile)
{
	ValidateEnvironmentProfile(ProfileType, Profile,
		[](UEnvironmentController* InController, const FEnvironmentProfile* InProfile)
		{
			InController->RemoveItem(InProfile->Priority);
		},
		TEXT("Environment Profile removed")
	);
}

