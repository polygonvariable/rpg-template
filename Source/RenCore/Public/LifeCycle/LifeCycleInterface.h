// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InstancedStruct.h"
#include "UObject/Interface.h"

#include "LifeCycleInterface.generated.h"


/**
 *
 */
UINTERFACE(MinimalAPI, Blueprintable, DisplayName = "LifeCycle Interface")
class ULifeCycleInterface : public UInterface
{
	GENERATED_BODY()
};


/**
 *
 */
class ILifeCycleInterface
{

	GENERATED_BODY()

public:

	bool bStarted = false;

	void StartLifecycle(UObject* Target, const FInstancedStruct Parameters, const bool bSkipLoad = true, const bool bSkipValidate = true);
	void OnLoaded(UObject* Target);

protected:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Meta = (ForceAsFunction, BlueprintProtected))
	void BeginStage(const FInstancedStruct Parameters);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Meta = (ForceAsFunction, BlueprintProtected))
	void LoadStage();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Meta = (ForceAsFunction, BlueprintProtected))
	bool ValidateStage();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Meta = (ForceAsFunction, BlueprintProtected))
	void ActivateStage();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Meta = (ForceAsFunction, BlueprintProtected))
	void EndStage();

};

