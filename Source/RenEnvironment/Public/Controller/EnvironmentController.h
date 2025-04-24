// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"

// Project Headers
#include "RenCore/Public/Priority/PrioritySystem.h"

// Generated Headers
#include "EnvironmentController.generated.h"

// Forward Declarations
class UTimer;


/**
 * 
 */
UCLASS(Abstract)
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
	void StartTransition();


	UFUNCTION()
	virtual void OnTransitioned(const float CurrentTime);

};


// UCLASS()
// class RENENVIRONMENT_API UEnvironmentFogController : public UEnvironmentController
// {

// 	GENERATED_BODY()

// public:

// 	UPROPERTY()
// 	TWeakObjectPtr<UExponentialHeightFogComponent> ExponentialHeightFog;

// protected:

// 	const FEnvironmentFogProfile* ActiveProfile;

// public:

// 	virtual void SetComponents(const TMap<uint8, TWeakObjectPtr<USceneComponent>>& Components) override;

// protected:

// 	virtual void HandleItemChanged(const FInstancedStruct& Item) override;
// 	virtual void OnTransitioned(const float CurrentTime) override;

// };

// UCLASS()
// class RENENVIRONMENT_API UEnvironmentLightController : public UEnvironmentController
// {

// 	GENERATED_BODY()

// public:

// 	UPROPERTY()
// 	TWeakObjectPtr<UDirectionalLightComponent> Sun;

// 	UPROPERTY()
// 	TWeakObjectPtr<UDirectionalLightComponent> Moon;

// protected:

// 	const FEnvironmentLightProfile* ActiveProfile;

// public:

// 	virtual void SetComponents(const TMap<uint8, TWeakObjectPtr<USceneComponent>>& Components) override;

// protected:

// 	virtual void HandleItemChanged(const FInstancedStruct& Item) override;
// 	virtual void OnTransitioned(const float CurrentTime) override;

// };

// UCLASS()
// class RENENVIRONMENT_API UEnvironmentAtmosphereController : public UEnvironmentController
// {

// 	GENERATED_BODY()

// public:

// 	UPROPERTY()
// 	TWeakObjectPtr<USkyAtmosphereComponent> Atmosphere;

// protected:

// 	const FEnvironmentAtmosphereProfile* ActiveProfile;

// public:

// 	virtual void SetComponents(const TMap<uint8, TWeakObjectPtr<USceneComponent>>& Components) override;

// protected:

// 	virtual void HandleItemChanged(const FInstancedStruct& Item) override;
// 	virtual void OnTransitioned(const float CurrentTime) override;

// };

