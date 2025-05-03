// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "InstancedStruct.h"

// Project Headers
#include "RenEnvironment/Public/Profile/WeatherProfile.h"

// Generated Headers
#include "SeasonSubsystem.generated.h"

// Forward Declarations
class UTimer;
class UPrioritySystem;
class UWeatherController;
class UMaterialParameterCollectionInstance;
class USeasonAsset;
class UGameClockSubsystem;
class UGameClockAsset;
class UEnvironmentAsset;


/**
 *
 */
UCLASS(Blueprintable)
class USeasonSubsystem : public UWorldSubsystem
{

	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void InitializeSeason();


	UFUNCTION(BlueprintCallable)
	void UpdateDay(int CurrentDay);


	UFUNCTION()
	USeasonAsset* GetSeasonAlpha(int CurrentDay, int TotalDays, float& Alpha, float& CurveAlpha) const;

protected:

	UMaterialParameterCollectionInstance* SeasonCollectionInstance;



	UPROPERTY()
	TObjectPtr<UGameClockSubsystem> GameClockSubsystem;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UGameClockAsset> GameClockAsset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UEnvironmentAsset> EnvironmentAsset;



	UFUNCTION()
	bool IsSeasonsValid() const;

	UFUNCTION()
	void HandleDayChange(int CurrentDay);

protected:

	virtual bool DoesSupportWorldType(EWorldType::Type WorldType) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	virtual void Deinitialize() override;
	virtual void PostInitialize() override;

};

