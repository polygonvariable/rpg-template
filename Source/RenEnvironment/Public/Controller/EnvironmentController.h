// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"

// Project Headers
#include "RenCore/Public/Priority/PrioritySystem.h"
#include "RenEnvironment/Public/Profile/EnvironmentProfileType.h"

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

	//UFUNCTION()
	//virtual void Initialize(const TMap<uint8, TWeakObjectPtr<USceneComponent>>& Components);

	//UFUNCTION()
	//virtual void Cleanup();

protected:
	
	UPROPERTY()
	TObjectPtr<UTimer> TransitionTimer;


	UFUNCTION()
	void StartTransition();


	UFUNCTION()
	void StopTransition();


	UFUNCTION()
	virtual void HandleTransitionTick(float CurrentTime);

protected:

	virtual void BeginDestroy();

};


// TODO:
// - Remove old controller
// - Add new controller, UEnvironmentDiscreteController to manage things like day/night cycle
// - Rename UEnvironmentController2 to UEnvironmentStackedController


/**
 *
 */
UCLASS(Abstract)
class UEnvironmentDiscreteController : public UObject
{

	GENERATED_BODY()

public:

	virtual void InitializeController();

};


/**
 *
 */
UCLASS(Abstract)
class RENENVIRONMENT_API UEnvironmentController2 : public UObjectPrioritySystem
{

	GENERATED_BODY()

public:

	UPROPERTY()
	TEnumAsByte<EEnvironmentProfileType> ProfileType;



	virtual void InitializeController();

};


