
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"
#include "InstancedStruct.h"

// Project Headers
#include "RenEnvironment/Public/Controller/EnvironmentController.h"
#include "RenEnvironment/Public/Profile/EnvironmentProfile.h"

// Generated Headers
#include "EnvironmentFogController.generated.h"

// Forward Declarations
class UExponentialHeightFogComponent;


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

protected:

	const FEnvironmentFogProfile* ActiveProfile;

public:

	virtual void SetComponents(const TMap<uint8, TWeakObjectPtr<USceneComponent>>& Components) override;

protected:

	virtual void HandleItemChanged(const FInstancedStruct& Item) override;
	virtual void HandleTransitionTick(float CurrentTime) override;

};

