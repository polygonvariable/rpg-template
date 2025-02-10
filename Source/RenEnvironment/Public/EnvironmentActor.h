// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// Generated Headers
#include "EnvironmentActor.generated.h"

// Forward Declarations
class USceneComponent;
class UOrbitalLightComponent;


/**
 *
 */
UCLASS(DisplayName = "Environment Actor")
class RENENVIRONMENT_API AEnvironmentActor : public AActor
{

	GENERATED_BODY()
	
public:

	AEnvironmentActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment|Time")
	float Time = 0.0f;


	UPROPERTY(BlueprintReadOnly, Category = "Default")
	TObjectPtr<USceneComponent> SceneComponent;


	UPROPERTY(BlueprintReadOnly, Category = "Default")
	TObjectPtr<UOrbitalLightComponent> SunLightComponent;


	UPROPERTY(BlueprintReadOnly, Category = "Default")
	TObjectPtr<UOrbitalLightComponent> MoonLightComponent;

protected:

	virtual void BeginPlay() override;

	virtual void ProcessUserConstructionScript();

public:

	virtual void Tick(float DeltaTime) override;

};
