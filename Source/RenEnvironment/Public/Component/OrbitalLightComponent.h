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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orbital Light|Time")
	float Time = 12.0f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orbital Light|Time")
	float TimeIncrement = 0.001f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orbital Light|Time")
	int DayLength = 300;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orbital Light|Time")
	bool bInverseRotation = false;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orbital Light|Date")
	int Year = 2022;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orbital Light|Date")
	int Month = 9;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orbital Light|Date")
	int Day = 21;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orbital Light|Location")
	float Latitude = 45.0f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orbital Light|Location")
	float Longitude = -73.0f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orbital Light|Location")
	float TimeZone = -4.0f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orbital Light|Location")
	float NorthPoleOffset = 0.0f;


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Orbital Light|Action")
	void SetTimeAndUpdate(float NewTime);
	virtual void SetTimeAndUpdate_Implementation(float NewTime);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Orbital Light|Action")
	void Update();
	virtual void Update_Implementation();

protected:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Orbital Light|Action")
	void GetHMS(const float InTime, int& OutHour, int& OutMinute, int& OutSecond);
	virtual void GetHMS_Implementation(const float InTime, int& OutHour, int& OutMinute, int& OutSecond);

};

