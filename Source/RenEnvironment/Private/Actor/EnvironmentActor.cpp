// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Actor/EnvironmentActor.h"

// Project Header
#include "RenGlobal/Public/Macro/GameInstanceMacro.h"
#include "RenGlobal/Public/Macro/LogMacro.h"
#include "RenCore/Public/Timer/Timer.h"

#include "Component/OrbitalLightComponent.h"
#include "Subsystem/EnvironmentSubsystem.h"

#include "Type/EnvironmentController.h"
#include "Controller/EnvironmentProfile.h"

#include "Components/SceneComponent.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Components/SkyAtmosphereComponent.h"
#include "Components/SkyLightComponent.h"
#include "Components/StaticMeshComponent.h"


AEnvironmentActor::AEnvironmentActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	if(IsValid(SceneComponent))
	{
		SceneComponent->SetupAttachment(GetRootComponent());

		SkyLight = CreateDefaultSubobject<USkyLightComponent>(TEXT("SkyLight"));
		if (IsValid(SkyLight))
		{
			SkyLight->SetupAttachment(SceneComponent);
			SkyLight->bRealTimeCapture = true;
			SkyLight->CubemapResolution = 32;
		}

		SkyAtmosphere = CreateDefaultSubobject<USkyAtmosphereComponent>(TEXT("SkyAtmosphere"));
		if (IsValid(SkyAtmosphere))
		{
			SkyAtmosphere->SetupAttachment(SceneComponent);
		}

		ExponentialHeightFog = CreateDefaultSubobject<UExponentialHeightFogComponent>(TEXT("ExponentialHeightFog"));
		if (IsValid(ExponentialHeightFog))
		{
			ExponentialHeightFog->SetupAttachment(SceneComponent);
			ExponentialHeightFog->FogDensity = 0.025f;
		}

		Sun = CreateDefaultSubobject<UOrbitalLightComponent>(TEXT("Sun"));
		if (IsValid(Sun))
		{
			Sun->SetupAttachment(SceneComponent);
			Sun->ForwardShadingPriority = 1;
			Sun->AtmosphereSunLightIndex = 0;
		}

		Moon = CreateDefaultSubobject<UOrbitalLightComponent>(TEXT("Moon"));
		if (IsValid(Moon))
		{
			Moon->SetupAttachment(SceneComponent);
			Moon->SpecularScale = 0.05f;
			Moon->Intensity = 5.0f;
			Moon->LightSourceAngle = 0.0f;
			Moon->bInverseRotation = true;
			Moon->ForwardShadingPriority = 0;
			Moon->AtmosphereSunLightIndex = 1;
			Moon->DynamicShadowCascades = 1;
			Moon->LightColor = FColor::FromHex("#4B6F91");
		}

		SkyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SkyMesh"));
		if (IsValid(SkyMesh))
		{
			SkyMesh->SetupAttachment(SceneComponent);
			SkyMesh->bCastDynamicShadow = false;
			SkyMesh->bCastStaticShadow = false;
			SkyMesh->bCastContactShadow = false;
			SkyMesh->bAffectDistanceFieldLighting = false;
			SkyMesh->PrimaryComponentTick.bStartWithTickEnabled = false;
		}
	}
}

void AEnvironmentActor::StartDayCycle()
{
	if (IsValid(DayCycleTimer))
	{
		LOG_ERROR(this, LogTemp, "DayCycleTimer is already valid");
		return;
	}

	DayCycleTimer = NewObject<UTimer>(this, UTimer::StaticClass());
	if(!IsValid(DayCycleTimer))
	{
		LOG_ERROR(this, LogTemp, "Failed to create DayCycleTimer");
		return;
	}

	DayCycleTimer->OnTick.AddDynamic(this, &AEnvironmentActor::UpdateDayCycle);
	DayCycleTimer->StartTimer(0.25f, 0); // Total Seconds in a Game's Day / (24 / Tick Rate)
}

void AEnvironmentActor::UpdateDayCycle(float CurrentTime, float TotalTime)
{
	Time += 0.025f;
	if (Time > 24.0f) Time = 0.0f;

	if (IsValid(Sun))
	{
		Sun->SetTime(Time);
		Sun->Update();
	}
	if (IsValid(Moon))
	{
		Moon->SetTime(Time);
		Moon->Update();
	}
}

void AEnvironmentActor::EndDayCycle()
{
	if (IsValid(DayCycleTimer))
	{
		DayCycleTimer->StopTimer();
	}
}

void AEnvironmentActor::InitializeEnvironmentControllers()
{
	//UEnvironmentFogController* FogController = NewObject<UEnvironmentFogController>(this, UEnvironmentFogController::StaticClass());
	//FogController->ExponentialHeightFog = ExponentialHeightFog;
	//UEnvironmentLightController* LightController = NewObject<UEnvironmentLightController>(this, UEnvironmentLightController::StaticClass());
	//LightController->Sun = Sun;
	//LightController->Moon = Moon;
	//UEnvironmentAtmosphereController* AtmosphereController = NewObject<UEnvironmentAtmosphereController>(this, UEnvironmentAtmosphereController::StaticClass());
	//AtmosphereController->Atmosphere = SkyAtmosphere;
	//EnvironmentControllers.Add(EEnvironmentProfileType::Fog, FogController);
	//EnvironmentControllers.Add(EEnvironmentProfileType::Light, LightController);
	//EnvironmentControllers.Add(EEnvironmentProfileType::Atmosphere, AtmosphereController);

	BREAK_GET_WORLDSUBSYSTEM(UEnvironmentSubsystem, EnvironmentSubsystem);

	TMap<uint8, TWeakObjectPtr<USceneComponent>> FogComponents;
	FogComponents.Add(0, ExponentialHeightFog);

	TMap<uint8, TWeakObjectPtr<USceneComponent>> LightComponents;
	LightComponents.Add(0, Sun);
	LightComponents.Add(1, Moon);

	TMap<uint8, TWeakObjectPtr<USceneComponent>> AtmosphereComponents;
	AtmosphereComponents.Add(0, SkyAtmosphere);

	EnvironmentSubsystem->AddEnvironmentController(EEnvironmentProfileType::Fog, UEnvironmentFogController::StaticClass(), FogComponents);
	EnvironmentSubsystem->AddEnvironmentController(EEnvironmentProfileType::Light, UEnvironmentLightController::StaticClass(), LightComponents);
	EnvironmentSubsystem->AddEnvironmentController(EEnvironmentProfileType::Atmosphere, UEnvironmentAtmosphereController::StaticClass(), AtmosphereComponents);

}

void AEnvironmentActor::AddEnvironmentProfile(const TEnumAsByte<EEnvironmentProfileType> ProfileType, FInstancedStruct Profile)
{
	//if(!Profile.IsValid())
	//{
	//	return;
	//}
	//if (const FEnvironmentProfile* ResolvedProfile = Profile.GetPtr<FEnvironmentProfile>())
	//{
	//	UEnvironmentController* Controller = *EnvironmentControllers.Find(ProfileType);
	//	if (IsValid(Controller))
	//	{
	//		Controller->AddItem(Profile, ResolvedProfile->Priority);
	//	}
	//}
}

void AEnvironmentActor::RemoveEnvironmentProfile(const TEnumAsByte<EEnvironmentProfileType> ProfileType, FInstancedStruct Profile)
{
	//if (!Profile.IsValid())
	//{
	//	return;
	//}
	//if (const FEnvironmentProfile* ResolvedProfile = Profile.GetPtr<FEnvironmentProfile>())
	//{
	//	UEnvironmentController* Controller = *EnvironmentControllers.Find(ProfileType);
	//	if (IsValid(Controller))
	//	{
	//		Controller->RemoveItem(ResolvedProfile->Priority);
	//	}
	//}
}

