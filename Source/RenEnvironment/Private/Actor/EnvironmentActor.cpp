// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Actor/EnvironmentActor.h"

// Project Header
#include "RenCore/Public/Timer/Timer.h"
#include "RenGlobal/Public/Library/MiscLibrary.h"
#include "RenGlobal/Public/Macro/LogMacro.h"

#include "RenGameplay/Public/GameClockSubsystem.h"

#include "Component/OrbitalLightComponent.h"
#include "Subsystem/EnvironmentSubsystem.h"

#include "Components/ExponentialHeightFogComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SkyAtmosphereComponent.h"
#include "Components/SkyLightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Controller/EnvironmentProfileType.h"
#include "Type/EnvironmentController.h"


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
	if (IsValid(DayCycleTimer) || !IsValid(GameClockSubsystem))
	{
		LOG_ERROR(LogTemp, "DayCycleTimer is already valid or GameClockSubsystem is not valid");
		return;
	}

	DayCycleTimer = NewObject<UTimer>(this);
	if(!IsValid(DayCycleTimer))
	{
		LOG_ERROR(LogTemp, "Failed to create DayCycleTimer");
		return;
	}

	DayCycleTimer->OnTick.AddDynamic(this, &AEnvironmentActor::HandleDayCycleTick);
	DayCycleTimer->StartTimer(0.1f, 0);
}


void AEnvironmentActor::HandleDayCycleTick(float CurrentTime)
{
	float NormalizedTime = GameClockSubsystem->GetSmoothNormalizedTimeOfDay();
	float RealTime = NormalizedTime * 24.0f;

	if (IsValid(Sun))
	{
		Sun->SetTime(RealTime);
		Sun->Update();
	}
	if (IsValid(Moon))
	{
		Moon->SetTime(RealTime);
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
	if(!IsValid(EnvironmentSubsystem)) return;

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


void AEnvironmentActor::BeginPlay()
{
	GetSubsystemReference<UGameClockSubsystem>(GetWorld(), GameClockSubsystem);
	GetSubsystemReference<UEnvironmentSubsystem>(GetWorld(), EnvironmentSubsystem);
	Super::BeginPlay();
}

