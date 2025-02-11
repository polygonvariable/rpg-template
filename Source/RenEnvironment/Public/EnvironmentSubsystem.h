// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"

// Project Headers
#include "RenCore/Public/Subsystem/RenWorldSubsystem.h"

// Generated Headers
#include "EnvironmentSubsystem.generated.h"

// Forward Declarations
class UPrioritySystem;


/**
 *
 */
UCLASS()
class RENENVIRONMENT_API UEnvironmentSubsystem : public URenWorldSubsystem
{

	GENERATED_BODY()

public:

	UEnvironmentSubsystem();


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration")
	TObjectPtr<UPrioritySystem> RegionPrioritySystem;

public:

	virtual void PostInitialize_Implementation() override;

};

