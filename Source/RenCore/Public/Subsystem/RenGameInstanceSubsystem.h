// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "RenGameInstanceSubsystem.generated.h"

class UGameMetadataSettings;


/**
 *
 */
UCLASS(Abstract, Blueprintable, DisplayName = "Ren Game Instance Subsystem")
class RENCORE_API URenGameInstanceSubsystem : public UGameInstanceSubsystem
{

	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta=(ForceAsFunction), Category = "Handler")
	void PostInitialize();
	virtual void PostInitialize_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta=(ForceAsFunction), Category = "Handler")
	void OnInitialized();
	virtual void OnInitialized_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta=(ForceAsFunction), Category = "Handler")
	void OnDeinitialized();
	virtual void OnDeinitialized_Implementation();

protected:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool ShouldCreateSubsystem(UObject* Object) const override;
	virtual UWorld* GetWorld() const override;

};

