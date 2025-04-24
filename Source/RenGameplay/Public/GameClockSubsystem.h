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

protected:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:

	UPROPERTY()
	float TotalSecondsInADay = 60.0f; // Total time of a day in game

	UFUNCTION(BlueprintCallable)
	void StartTimer();

	UFUNCTION(BlueprintCallable)
	void StopTimer();

	UFUNCTION(BlueprintCallable)
	float GetTimeOfTheDay() const;

	UFUNCTION(BlueprintPure)
	FString GetFormattedTimeOfDay() const;

	UFUNCTION(BlueprintPure)
	float GetNormalizedTimeOfDay() const;

	UFUNCTION(BlueprintCallable)
	float GetSmoothNormalizedTimeOfDay() const;

	UFUNCTION(BlueprintPure)
	float GetRealTimeOfDay() const;

	UFUNCTION(BlueprintPure)
	bool IsDay() const;

	UFUNCTION(BlueprintPure)
	bool IsNight() const;

	UFUNCTION(BlueprintCallable)
	int GetTotalDays() const;

protected:

	UPROPERTY()
	TObjectPtr<UTimer> ClockTimer;

	UPROPERTY()
	TWeakObjectPtr<UStorage> Storage;

	UPROPERTY()
	int DayCounter = 0;

	UPROPERTY()
	float TimeOfTheDay = 0.0f; // Clamped from 0 and TotalSecondsInADay

	UPROPERTY()
	float LastTickAt = 0.0f;

	UFUNCTION()
	void HandleClockTick(float CurrentTime);

	UFUNCTION()
	void LoadStoredTime();

	UFUNCTION()
	void SaveStoredTime();

	FDelegateHandle OnWorldBeginTearDownHandle;
	virtual void HandleWorldBeginTearDown(UWorld* World);

public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDayChanged, int, Day);
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnDayChanged OnDayChanged;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimeChanged, float, Time);
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnTimeChanged OnTimeChanged;

};

