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

