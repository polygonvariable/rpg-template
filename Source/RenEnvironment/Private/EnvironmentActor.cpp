// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "EnvironmentActor.h"

// Project Header
#include "RenShared/Public/Macro/GameInstanceMacro.h"
#include "RenShared/Public/Macro/LogMacro.h"
#include "Component/OrbitalLightComponent.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Components/SceneComponent.h"
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

		SkyLightComponent = CreateDefaultSubobject<USkyLightComponent>(TEXT("SkyLight"));
		if (IsValid(SkyLightComponent))
		{
			SkyLightComponent->SetupAttachment(SceneComponent);
			SkyLightComponent->bRealTimeCapture = true;
			SkyLightComponent->CubemapResolution = 64;
			SkyLightComponent->PrimaryComponentTick.bStartWithTickEnabled = false;
		}

		SkyAtmosphereComponent = CreateDefaultSubobject<USkyAtmosphereComponent>(TEXT("SkyAtmosphere"));
		if (IsValid(SkyAtmosphereComponent))
		{
			SkyAtmosphereComponent->SetupAttachment(SceneComponent);
			SkyAtmosphereComponent->PrimaryComponentTick.bStartWithTickEnabled = false;
		}

		ExponentialHeightFogComponent = CreateDefaultSubobject<UExponentialHeightFogComponent>(TEXT("ExponentialHeightFog"));
		if (IsValid(ExponentialHeightFogComponent))
		{
			ExponentialHeightFogComponent->SetupAttachment(SceneComponent);
			ExponentialHeightFogComponent->FogDensity = 0.025f;
			ExponentialHeightFogComponent->PrimaryComponentTick.bStartWithTickEnabled = false;
		}

		SunLightComponent = CreateDefaultSubobject<UOrbitalLightComponent>(TEXT("Sun"));
		if (IsValid(SunLightComponent))
		{
			SunLightComponent->SetupAttachment(SceneComponent);
			SunLightComponent->ForwardShadingPriority = 1;
			SunLightComponent->AtmosphereSunLightIndex = 0;
		}

		MoonLightComponent = CreateDefaultSubobject<UOrbitalLightComponent>(TEXT("Moon"));
		if (IsValid(MoonLightComponent))
		{
			MoonLightComponent->SetupAttachment(SceneComponent);
			MoonLightComponent->SpecularScale = 0.05f;
			MoonLightComponent->Intensity = 5.0f;
			MoonLightComponent->bInverseRotation = true;
			MoonLightComponent->ForwardShadingPriority = 0;
			MoonLightComponent->AtmosphereSunLightIndex = 1;
			MoonLightComponent->DynamicShadowCascades = 1;
			MoonLightComponent->LightColor = FColor::FromHex("#4B6F91");
		}

		SkyDome = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SkyDome"));
		if (IsValid(SkyDome))
		{
			SkyDome->SetupAttachment(SceneComponent);
			SkyDome->bCastDynamicShadow = false;
			SkyDome->bCastStaticShadow = false;
			SkyDome->bCastContactShadow = false;
			SkyDome->bAffectDistanceFieldLighting = false;
			SkyDome->PrimaryComponentTick.bStartWithTickEnabled = false;
		}
	}
}

void AEnvironmentActor::BeginPlay()
{
	Super::BeginPlay();
}

