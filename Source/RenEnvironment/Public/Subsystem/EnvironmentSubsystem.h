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
class UEnvironmentController2;
class UEnvironmentProfileAsset;


/**
 *
 */
UCLASS(Blueprintable) // Add Blueprintable for easiy debug in live blueprint debugger
class RENENVIRONMENT_API UEnvironmentSubsystem : public UWorldSubsystem
{

	GENERATED_BODY()

public:

	UFUNCTION()
	bool CreateController(const TEnumAsByte<EEnvironmentProfileType> ProfileType, TSubclassOf<UEnvironmentController2> ControllerClass);


	UFUNCTION()
	bool AddEnvironmentController(const TEnumAsByte<EEnvironmentProfileType> ProfileType, TSubclassOf<UEnvironmentController> ControllerClass, const TMap<uint8, TWeakObjectPtr<USceneComponent>>& Components);

	UFUNCTION()
	bool RemoveEnvironmentController(const TEnumAsByte<EEnvironmentProfileType> ProfileType);


	UFUNCTION(BlueprintCallable)
	void AddEnvironmentProfile(const TEnumAsByte<EEnvironmentProfileType> ProfileType, FInstancedStruct Profile);


	UFUNCTION(BlueprintCallable)
	void RemoveEnvironmentProfile(const TEnumAsByte<EEnvironmentProfileType> ProfileType, FInstancedStruct Profile);



	UFUNCTION(BlueprintCallable)
	void AddEnvironmentProfile2(UEnvironmentProfileAsset* ProfileAsset, int Priority);

	UFUNCTION(BlueprintCallable)
	void RemoveEnvironmentProfile2(TEnumAsByte<EEnvironmentProfileType> ProfileType, int Priority);

protected:

	UPROPERTY(BlueprintReadOnly)
	TMap<TEnumAsByte<EEnvironmentProfileType>, TObjectPtr<UEnvironmentController>> EnvironmentControllers;

	UPROPERTY(BlueprintReadOnly)
	TMap<TEnumAsByte<EEnvironmentProfileType>, TObjectPtr<UEnvironmentController2>> EnvironmentControllers2;


	void ValidateEnvironmentProfile(const TEnumAsByte<EEnvironmentProfileType> ProfileType, const FInstancedStruct Profile, TFunctionRef<void(UEnvironmentController* Controller, const FEnvironmentProfile* Profile)> Callback, const FString& LogMessage);

protected:

	virtual bool DoesSupportWorldType(EWorldType::Type WorldType) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

};

