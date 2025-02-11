// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Component/OrbitalLightComponent.h"
#include "SunPosition/Public/SunPosition.h"


UOrbitalLightComponent::UOrbitalLightComponent()
{
	PrimaryComponentTick.bStartWithTickEnabled = false;

	Intensity = 20.0f;
	LightSourceAngle = 4.0f;

	FarShadowCascadeCount = 1;
	DynamicShadowCascades = 2;
	DynamicShadowDistanceMovableLight = 4000.0f;
}

void UOrbitalLightComponent::SetTime_Implementation(float NewTime)
{
	Time = NewTime;
	Update();
}

float UOrbitalLightComponent::GetTime_Implementation()
{
	return Time;
}

void UOrbitalLightComponent::Update_Implementation()
{
	int Hour, Minute, Second;
	GetHMS(Time, Hour, Minute, Second);
	
	FSunPositionData SunPositionData;
	USunPositionFunctionLibrary::GetSunPosition(
	    Latitude,
	    Longitude,
	    TimeZone,
	    true,
	    Year,
	    Month,
	    Day,
	    Hour,
	    Minute,
	    Second,
	    SunPositionData
	);
	
	float RotationOrientation = bInverseRotation ? -1 : 1;
	float RotationYaw = (SunPositionData.Azimuth + NorthPoleOffset) * RotationOrientation;
	float RotationPitch = SunPositionData.CorrectedElevation * RotationOrientation;
	
	SetRelativeRotation(FRotator(RotationPitch, RotationYaw, 0.0f));
}

void UOrbitalLightComponent::GetHMS_Implementation(const float InTime, int& OutHour, int& OutMinute, int& OutSecond)
{
	OutHour = static_cast<int>(InTime) % 24;
	
	float MinuteFraction = (InTime - OutHour) * 60.0f;
	OutMinute = static_cast<int>(MinuteFraction) % 60;
	
	float SecondFraction = (MinuteFraction - OutMinute) * 60.0f;
	OutSecond = static_cast<int>(SecondFraction) % 60;
}
