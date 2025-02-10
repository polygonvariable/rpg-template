// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Component/OrbitalLightComponent.h"
#include "SunPosition/Public/SunPosition.h"


void UOrbitalLightComponent::Update_Implementation()
{
	int HMSHour, HMSMinute, HMSSecond;
	GetHMS(Time, HMSHour, HMSMinute, HMSSecond);
	
	FSunPositionData SunPositionData;
	USunPositionFunctionLibrary::GetSunPosition(
	    Latitude,
	    Longitude,
	    TimeZone,
	    false,
	    Year,
	    Month,
	    Day,
	    HMSHour,
	    HMSMinute,
	    HMSSecond,
	    SunPositionData
	);
	
	float RotationOrientation = bInverseRotation ? -1 : 1;
	float RotationY = (SunPositionData.Azimuth + NorthPoleOffset) * RotationOrientation;
	float RotationZ = SunPositionData.CorrectedElevation * RotationOrientation;
	
	SetRelativeRotation(FRotator(RotationY, RotationZ, 0));
}

void UOrbitalLightComponent::SetTimeAndUpdate_Implementation(float NewTime)
{
	Time = NewTime;
	Update();
}

void UOrbitalLightComponent::GetHMS_Implementation(const float InTime, int& OutHour, int& OutMinute, int& OutSecond)
{
	OutHour = static_cast<int>(InTime) % 24;
	
	float MinuteFraction = (InTime - OutHour) * 60.0f;
	OutMinute = static_cast<int>(MinuteFraction) % 60;
	
	float SecondFraction = (MinuteFraction - OutMinute) * 60.0f;
	OutSecond = static_cast<int>(SecondFraction) % 60;
}
