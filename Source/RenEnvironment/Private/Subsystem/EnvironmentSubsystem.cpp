// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Subsystem/EnvironmentSubsystem.h"

// Engine Header
#include "EngineUtils.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"

// Project Header
#include "RenCore/Public/Developer/GameMetadataSettings.h"
#include "RenGlobal/Public/Macro/LogMacro.h"

#include "Profile/EnvironmentProfile.h"
#include "Controller/EnvironmentController.h"

#include "Asset/EnvironmentAsset.h"
#include "Asset/EnvironmentProfileAsset.h"
#include "Controller/EnvironmentLightController.h"
#include "Controller/EnvironmentFogController.h"
#include "Controller/EnvironmentAtmosphereController.h"




bool UEnvironmentSubsystem::CreateController(const TEnumAsByte<EEnvironmentProfileType> ProfileType, TSubclassOf<UEnvironmentController2> ControllerClass)
{
	if (EnvironmentControllers.Contains(ProfileType))
	{
		LOG_ERROR(LogTemp, "Environment Controller already exists");
		return false;
	}

	UEnvironmentController2* Controller = NewObject<UEnvironmentController2>(this, ControllerClass);
	if (!IsValid(Controller))
	{
		LOG_ERROR(LogTemp, "Failed to create Environment Controller");
		return false;
	}

	Controller->InitializeController();
	EnvironmentControllers2.Add(ProfileType, Controller);

	return true;
}

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

bool UEnvironmentSubsystem::RemoveEnvironmentController(const TEnumAsByte<EEnvironmentProfileType> ProfileType)
{
	if (!EnvironmentControllers.Contains(ProfileType))
	{
		LOG_ERROR(LogTemp, "Environment Controller does not exist");
		return false;
	}
	EnvironmentControllers.Remove(ProfileType);
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




void UEnvironmentSubsystem::AddEnvironmentProfile2(UEnvironmentProfileAsset* ProfileAsset, int Priority)
{
	if(IsValid(ProfileAsset))
	{
		PRINT_ERROR(LogTemp, 2.0f, TEXT("ProfileAsset is not valid"));
		return;
	}

	if (UEnvironmentController2* Controller = EnvironmentControllers2.FindRef(ProfileAsset->ProfileType))
	{
		Controller->AddItem(ProfileAsset, Priority);
	}
}

void UEnvironmentSubsystem::RemoveEnvironmentProfile2(TEnumAsByte<EEnvironmentProfileType> ProfileType, int Priority)
{
	if (UEnvironmentController2* Controller = EnvironmentControllers2.FindRef(ProfileType))
	{
		Controller->RemoveItem(Priority);
	}
}




bool UEnvironmentSubsystem::DoesSupportWorldType(EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

void UEnvironmentSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	LOG_WARNING(LogTemp, TEXT("EnvironmentSubsystem initialized"));
}

void UEnvironmentSubsystem::Deinitialize()
{
	LOG_WARNING(LogTemp, TEXT("EnvironmentSubsystem deinitialized"));

	for(TPair<TEnumAsByte<EEnvironmentProfileType>, TObjectPtr<UEnvironmentController2>>& Kvp : EnvironmentControllers2)
	{
		Kvp.Value->MarkAsGarbage();
	}
	EnvironmentControllers2.Empty();

	Super::Deinitialize();
}

void UEnvironmentSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	LOG_WARNING(LogTemp, TEXT("EnvironmentSubsystem OnWorldBeginPlay"));


	if (const UGameMetadataSettings* GameMetadata = GetDefault<UGameMetadataSettings>())
	{
		if (GameMetadata->EnvironmentAsset.IsNull())
		{
			PRINT_ERROR(LogTemp, 2.0f, TEXT("EnvironmentAsset is not valid"));
			return;
		}

		UEnvironmentAsset* EnvironmentAsset = Cast<UEnvironmentAsset>(GameMetadata->EnvironmentAsset.LoadSynchronous());
		if (!IsValid(EnvironmentAsset))
		{
			PRINT_ERROR(LogTemp, 2.0f, TEXT("Environment cast failed or is not valid"));
			return;
		}

		for (TPair<TEnumAsByte<EEnvironmentProfileType>, TSubclassOf<UEnvironmentController2>>& Kvp : EnvironmentAsset->EnvironmentControllers)
		{
			CreateController(Kvp.Key, Kvp.Value);
		}

	}

	//CreateController(EEnvironmentProfileType::Light, UEnvironmentLightController2::StaticClass());
	//CreateController(EEnvironmentProfileType::Fog, UEnvironmentFogController2::StaticClass());
	//CreateController(EEnvironmentProfileType::Atmosphere, UEnvironmentAtmosphereController2::StaticClass());
}

