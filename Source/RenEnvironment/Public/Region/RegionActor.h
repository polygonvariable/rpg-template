// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InstancedStruct.h"

// Project Headers
#include "Profile/EnvironmentProfile.h"
#include "Profile/EnvironmentProfileType.h"

// Generated Headers
#include "RegionActor.generated.h"

// Forward Declarations
class UEnvironmentSubsystem;

/**
 *
 */
UCLASS()
class RENENVIRONMENT_API ARegionActor : public AActor
{

	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (BaseStruct = "/Script/RenEnvironment.EnvironmentProfile"))
	TMap<TEnumAsByte<EEnvironmentProfileType>,FInstancedStruct> EnvironmentProfiles;

protected:

	UPROPERTY()
	TObjectPtr<UEnvironmentSubsystem> EnvironmentSubsystem;

	UFUNCTION(BlueprintCallable)
	void HandlePlayerEntered();

	UFUNCTION(BlueprintCallable)
	void HandlePlayerExited();

};
