// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"
#include "InstancedStruct.h"

#include "Components/ExponentialHeightFogComponent.h"
#include "Components/SkyAtmosphereComponent.h"
#include "Components/DirectionalLightComponent.h"

// Project Headers
#include "RenCore/Public/Priority/PrioritySystem.h"
#include "RenEnvironment/Public/Controller/EnvironmentProfile.h"

// Generated Headers
#include "EnvironmentController.generated.h"


class UTimer;

/**
 * 
 */
UCLASS()
class RENENVIRONMENT_API UEnvironmentController : public UPrioritySystem
{

	GENERATED_BODY()

public:

	UFUNCTION()
	virtual void SetComponents(const TMap<uint8, TWeakObjectPtr<USceneComponent>>& Components);

protected:
	
	UPROPERTY()
	TObjectPtr<UTimer> TransitionTimer;


	UFUNCTION()
	void SetTimer();


	UFUNCTION()
	virtual void OnTransitioned(const float CurrentTime);

};


/**
 *
 */
UCLASS()
class RENENVIRONMENT_API UEnvironmentFogController : public UEnvironmentController
{

	GENERATED_BODY()

public:

	UPROPERTY()
	TWeakObjectPtr<UExponentialHeightFogComponent> ExponentialHeightFog;

	virtual void SetComponents(const TMap<uint8, TWeakObjectPtr<USceneComponent>>& Components) override;

protected:

	const FEnvironmentFogProfile* ActiveProfile;

	virtual void OnActiveItemChanged_Implementation() override;

	virtual void OnTransitioned(const float CurrentTime) override;

};


/**
 *
 */
UCLASS()
class RENENVIRONMENT_API UEnvironmentLightController : public UEnvironmentController
{

	GENERATED_BODY()

public:

	UPROPERTY()
	TWeakObjectPtr<UDirectionalLightComponent> Sun;

	UPROPERTY()
	TWeakObjectPtr<UDirectionalLightComponent> Moon;

	virtual void SetComponents(const TMap<uint8, TWeakObjectPtr<USceneComponent>>& Components) override;

protected:

	const FEnvironmentLightProfile* ActiveProfile;

	virtual void OnActiveItemChanged_Implementation() override;

	virtual void OnTransitioned(const float CurrentTime) override;

};


/**
 *
 */
UCLASS()
class RENENVIRONMENT_API UEnvironmentAtmosphereController : public UEnvironmentController
{

	GENERATED_BODY()

public:

	UPROPERTY()
	TWeakObjectPtr<USkyAtmosphereComponent> Atmosphere;

	virtual void SetComponents(const TMap<uint8, TWeakObjectPtr<USceneComponent>>& Components) override;

protected:

	const FEnvironmentAtmosphereProfile* ActiveProfile;

	virtual void OnActiveItemChanged_Implementation() override;

	virtual void OnTransitioned(const float CurrentTime) override;

};

