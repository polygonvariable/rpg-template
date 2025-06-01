// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"

// Generated Headers
#include "GameClockSubsystem.generated.h"

// Forward Declarations
class UTimer;
class UGameClockAsset;
class IGameClockInterface;


/**
 *
 */
UCLASS()
class RENGAMEPLAY_API UGameClockSubsystem : public UWorldSubsystem
{

	GENERATED_BODY()

public:

	UPROPERTY()
	float TotalSecondsInADay = 60.0f; // Total time of a day in game

	UPROPERTY()
	int TotalDaysInAYear = 30; // Total days in game to complete a year



	UFUNCTION(BlueprintPure)
	UGameClockAsset* GetClockAsset() const;



	UFUNCTION()
	void StartClock();

	UFUNCTION()
	void StopClock();



	UFUNCTION(BlueprintCallable)
	float GetCurrentTime() const;

	UFUNCTION(BlueprintPure)
	FString GetFormattedTime(const FString& Format = TEXT("hh:mm:ss ap")) const;

	UFUNCTION(BlueprintPure)
	float GetNormalizedTime() const;

	UFUNCTION(BlueprintCallable)
	float GetSmoothNormalizedTime() const;

	UFUNCTION(BlueprintPure)
	float GetSimulatedRealTime() const;



	UFUNCTION(BlueprintCallable)
	int GetCurrentDay() const;

	UFUNCTION(BlueprintPure)
	bool IsDay() const;

	UFUNCTION(BlueprintPure)
	bool IsNight() const;



	UFUNCTION(BlueprintPure)
	bool IsActive() const;

protected:

	FDelegateHandle OnWorldBeginTearDownHandle;

	TWeakInterfacePtr<IGameClockInterface> GameClockInterface;



	UPROPERTY()
	TObjectPtr<UGameClockAsset> ClockAsset;
	
	UPROPERTY()
	TObjectPtr<UTimer> ClockTimer;

	// UPROPERTY()
	// TWeakObjectPtr<UStorage> Storage;

	UPROPERTY()
	int CurrentDay = 1; // Clamped from 1 and TotalDaysInAYear

	UPROPERTY()
	float CurrentTime = 0.0f; // Clamped from 0 and TotalSecondsInADay

	UPROPERTY()
	float LastTickAt = 0.0f;



	UFUNCTION()
	void CreateClock();

	UFUNCTION()
	void CleanupClock();



	UFUNCTION()
	void LoadWorldTime();

	UFUNCTION()
	void SaveWorldTime();



	UFUNCTION()
	void HandleClockTick(float ElapsedTime);

	UFUNCTION()
	void HandleWorldBeginTearDown(UWorld* World);

protected:

	virtual bool DoesSupportWorldType(EWorldType::Type WorldType) const override;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void OnWorldComponentsUpdated(UWorld& InWorld) override;

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

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

