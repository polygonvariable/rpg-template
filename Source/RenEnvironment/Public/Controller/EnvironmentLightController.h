
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"
#include "InstancedStruct.h"
#include "Components/DirectionalLightComponent.h"

// Project Headers
#include "RenEnvironment/Public/Controller/EnvironmentController.h"
#include "RenEnvironment/Public/Profile/EnvironmentProfile.h"

// Generated Headers
#include "EnvironmentLightController.generated.h"

// Forward Declarations
class UDirectionalLightComponent;


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

protected:

	const FEnvironmentLightProfile* ActiveProfile;

public:

	virtual void SetComponents(const TMap<uint8, TWeakObjectPtr<USceneComponent>>& Components) override;

protected:

	virtual void HandleItemChanged(const FInstancedStruct& Item) override;
	virtual void OnTransitioned(const float CurrentTime) override;

};

