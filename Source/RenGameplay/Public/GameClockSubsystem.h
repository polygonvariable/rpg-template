// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"

// Generated Headers
#include "GameClockSubsystem.generated.h"

// Forward Declarations
class UTimer;
class UStorage;


/**
 *
 */
UCLASS()
class RENGAMEPLAY_API UGameClockSubsystem : public UWorldSubsystem
{

	GENERATED_BODY()

public:

	UPROPERTY()
	bool bAutoStart = true;

	UPROPERTY()
	float TotalSecondsInADay = 60.0f; // Total time of a day in game



	UFUNCTION()
	void StartClock();

	UFUNCTION()
	void StopClock();



	UFUNCTION(BlueprintCallable)
	float GetTimeOfTheDay() const;

	UFUNCTION(BlueprintPure)
	FString GetFormattedTimeOfDay(const FString& Format = TEXT("hh:mm:ss ap")) const;

	UFUNCTION(BlueprintPure)
	float GetNormalizedTimeOfDay() const;

	UFUNCTION(BlueprintCallable)
	float GetSmoothNormalizedTimeOfDay() const;

	UFUNCTION(BlueprintPure)
	float GetSimulatedRealTimeOfDay() const;



	UFUNCTION(BlueprintCallable)
	int GetDay() const;

	UFUNCTION(BlueprintPure)
	bool IsDay() const;

	UFUNCTION(BlueprintPure)
	bool IsNight() const;

protected:

	FDelegateHandle OnWorldBeginTearDownHandle;



	UPROPERTY()
	TObjectPtr<UTimer> ClockTimer;

	UPROPERTY()
	TWeakObjectPtr<UStorage> Storage;



	UPROPERTY()
	int DayCount = 0;

	UPROPERTY()
	float TimeOfTheDay = 0.0f; // Clamped from 0 and TotalSecondsInADay

	UPROPERTY()
	float LastTickAt = 0.0f;



	UFUNCTION()
	void InitializeClock();

	UFUNCTION()
	void CleanupClock();



	UFUNCTION()
	void LoadWorldTime();

	UFUNCTION()
	void SaveWorldTime();



	UFUNCTION()
	void HandleClockTick(float CurrentTime);

	UFUNCTION()
	void HandleWorldBeginTearDown(UWorld* World);

protected:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDayChanged, int, Day);
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnDayChanged OnDayChanged;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimeChanged, float, Time);
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnTimeChanged OnTimeChanged;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClockStarted);
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnClockStarted OnClockStarted;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClockStopped);
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnClockStopped OnClockStopped;

};

