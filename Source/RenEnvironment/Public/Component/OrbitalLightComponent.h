// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"
#include "Components/DirectionalLightComponent.h"

// Generated Headers
#include "OrbitalLightComponent.generated.h"


/**
 * 
 */
UCLASS(ClassGroup = (Custom), Meta = (BlueprintSpawnableComponent))
class RENENVIRONMENT_API UOrbitalLightComponent : public UDirectionalLightComponent
{

	GENERATED_BODY()

public:

	UOrbitalLightComponent();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (UIMin = "0.0001", ClampMin = "0.0001"), Category = "Orbital Light|Time")
	float TimeIncrement = 0.001f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (UIMin = "5", ClampMin = "5"), Category = "Orbital Light|Time")
	int DayLength = 300;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orbital Light|Time")
	bool bInverseRotation = false;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (UIMin = "1800", UIMax = "2200", ClampMax = "4000", ClampMin = "0"), Category = "Orbital Light|Date")
	int Year = 2022;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (UIMin = "1", ClampMin = "1", UIMax = "12", ClampMax = "12"), Category = "Orbital Light|Date")
	int Month = 9;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (UIMin = "1", ClampMin = "1", UIMax = "31", ClampMax = "31"), Category = "Orbital Light|Date")
	int Day = 21;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (UIMin = "-89.99", ClampMin = "-89.99", UIMax = "89.99", ClampMax = "89.99"), Category = "Orbital Light|Location")
	float Latitude = 45.0f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (UIMax = "180", UIMin = "-180", ClampMin = "-180", ClampMax = "180"), Category = "Orbital Light|Location")
	float Longitude = -73.0f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (UIMin = "-12", ClampMin = "-12", UIMax = "14", ClampMax = "14"), Category = "Orbital Light|Location")
	float TimeZone = -4.0f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (UIMin = "-360", ClampMin = "-360", UIMax = "360", ClampMax = "360"), Category = "Orbital Light|Location")
	float NorthPoleOffset = 0.0f;


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Orbital Light|Action")
	void SetTime(float NewTime);
	virtual void SetTime_Implementation(float NewTime);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Orbital Light|Action")
	float GetTime();
	virtual float GetTime_Implementation();


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Orbital Light|Action")
	void Update();
	virtual void Update_Implementation();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (UIMin = "0", UIMax = "24", ClampMin = "0", ClampMax = "24"), Category = "Orbital Light|Time")
	float Time = 12.0f;


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Orbital Light|Action")
	void GetHMS(const float InTime, int& OutHour, int& OutMinute, int& OutSecond);
	virtual void GetHMS_Implementation(const float InTime, int& OutHour, int& OutMinute, int& OutSecond);

};

