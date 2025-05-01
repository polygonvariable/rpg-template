// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"

// Project Headers
#include "RenEnvironment/Public/Profile/EnvironmentProfile.h"
#include "RenEnvironment/Public/Profile/EnvironmentProfileType.h"

// Generated Headers
#include "EnvironmentSubsystem.generated.h"

// Forward Declarations
class UEnvironmentController;


/**
 *
 */
UCLASS(Blueprintable) // Add Blueprintable for easiy debug in live blueprint debugger
class RENENVIRONMENT_API UEnvironmentSubsystem : public UWorldSubsystem
{

	GENERATED_BODY()

public:

	UFUNCTION()
	bool AddEnvironmentController(const TEnumAsByte<EEnvironmentProfileType> ProfileType, TSubclassOf<UEnvironmentController> ControllerClass, const TMap<uint8, TWeakObjectPtr<USceneComponent>>& Components);

	UFUNCTION()
	bool RemoveEnvironmentController(const TEnumAsByte<EEnvironmentProfileType> ProfileType);


	UFUNCTION(BlueprintCallable)
	void AddEnvironmentProfile(const TEnumAsByte<EEnvironmentProfileType> ProfileType, FInstancedStruct Profile);


	UFUNCTION(BlueprintCallable)
	void RemoveEnvironmentProfile(const TEnumAsByte<EEnvironmentProfileType> ProfileType, FInstancedStruct Profile);

protected:

	UPROPERTY(BlueprintReadOnly)
	TMap<TEnumAsByte<EEnvironmentProfileType>, TObjectPtr<UEnvironmentController>> EnvironmentControllers;


	void ValidateEnvironmentProfile(const TEnumAsByte<EEnvironmentProfileType> ProfileType, const FInstancedStruct Profile, TFunctionRef<void(UEnvironmentController* Controller, const FEnvironmentProfile* Profile)> Callback, const FString& LogMessage);

};

