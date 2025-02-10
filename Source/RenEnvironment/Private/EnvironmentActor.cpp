// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "EnvironmentActor.h"

// Project Header
#include "Components/SceneComponent.h"
#include "Component/OrbitalLightComponent.h"


AEnvironmentActor::AEnvironmentActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	if(IsValid(SceneComponent))
	{
		SceneComponent->SetupAttachment(GetRootComponent());

		SunLightComponent = CreateDefaultSubobject<UOrbitalLightComponent>(TEXT("SunLightComponent"));
		if (IsValid(SunLightComponent))
		{
			SunLightComponent->SetupAttachment(SceneComponent);
		}
		MoonLightComponent = CreateDefaultSubobject<UOrbitalLightComponent>(TEXT("MoonLightComponent"));
		if (IsValid(MoonLightComponent))
		{
			MoonLightComponent->SetupAttachment(SceneComponent);
			MoonLightComponent->bInverseRotation = true;
		}
	}
}

void AEnvironmentActor::BeginPlay()
{
	Super::BeginPlay();
}

void AEnvironmentActor::ProcessUserConstructionScript()
{
	if (IsValid(SunLightComponent) && IsValid(MoonLightComponent))
	{
		SunLightComponent->SetTimeAndUpdate(Time);
		MoonLightComponent->SetTimeAndUpdate(Time);
	}
}

void AEnvironmentActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

