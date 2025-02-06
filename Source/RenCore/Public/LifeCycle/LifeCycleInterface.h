// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"
#include "InstancedStruct.h"
#include "UObject/Interface.h"

// Generated Headers
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
class RENCORE_API ILifeCycleInterface
{

	GENERATED_BODY()

public:

	bool bStarted = false;

	void StartLifecycle(UObject* Target, FInstancedStruct Parameters, const bool bSkipLoad = true, const bool bSkipValidate = true);
	void OnLoaded(UObject* Target);

protected:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Meta = (ForceAsFunction, BlueprintProtected))
	void BeginStage(FInstancedStruct Parameters);


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Meta = (ForceAsFunction, BlueprintProtected))
	void LoadStage();


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Meta = (ForceAsFunction, BlueprintProtected))
	bool ValidateStage();


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Meta = (ForceAsFunction, BlueprintProtected))
	void ActivateStage();


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Meta = (ForceAsFunction, BlueprintProtected))
	void EndStage();

};

