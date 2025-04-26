
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"
#include "InstancedStruct.h"

// Project Headers
#include "RenEnvironment/Public/Controller/EnvironmentController.h"
#include "RenEnvironment/Public/Profile/EnvironmentProfile.h"

// Generated Headers
#include "EnvironmentAtmosphereController.generated.h"

// Forward Declarations
class USkyAtmosphereComponent;


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

protected:

	const FEnvironmentAtmosphereProfile* ActiveProfile;

public:

	virtual void SetComponents(const TMap<uint8, TWeakObjectPtr<USceneComponent>>& Components) override;

protected:

	virtual void HandleItemChanged(const FInstancedStruct& Item) override;
	virtual void HandleTransitionTick(float CurrentTime) override;

};

