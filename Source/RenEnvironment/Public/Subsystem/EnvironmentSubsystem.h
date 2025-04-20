// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"

// Project Headers
#include "RenEnvironment/Public/Controller/EnvironmentProfile.h"
#include "RenEnvironment/Public/Controller/EnvironmentProfileType.h"

// Generated Headers
#include "EnvironmentSubsystem.generated.h"


class UTimer;
class UEnvironmentController;


UCLASS()
class RENENVIRONMENT_API UEnvironmentSubsystem : public UWorldSubsystem
{

	GENERATED_BODY()

public:

	UFUNCTION()
	bool AddEnvironmentController(const TEnumAsByte<EEnvironmentProfileType> ProfileType, TSubclassOf<UEnvironmentController> ControllerClass, const TMap<uint8, TWeakObjectPtr<USceneComponent>>& Components);

	UFUNCTION(BlueprintCallable)
	void AddEnvironmentProfile(const TEnumAsByte<EEnvironmentProfileType> ProfileType, FInstancedStruct Profile);


	UFUNCTION(BlueprintCallable)
	void RemoveEnvironmentProfile(const TEnumAsByte<EEnvironmentProfileType> ProfileType, FInstancedStruct Profile);

protected:

	UPROPERTY()
	TMap<TEnumAsByte<EEnvironmentProfileType>, TObjectPtr<UEnvironmentController>> EnvironmentControllers;

	void ValidateProfile(const TEnumAsByte<EEnvironmentProfileType> ProfileType, const FInstancedStruct Profile, TFunctionRef<void(UEnvironmentController* Controller, const FEnvironmentProfile* Profile)> Callback, const FString& LogMessage);

};

