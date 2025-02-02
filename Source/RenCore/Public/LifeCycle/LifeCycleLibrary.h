// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InstancedStruct.h"

#include "LifeCycleLibrary.generated.h"


/**
 *
 */
UCLASS(MinimalAPI, DisplayName = "LifeCycle Interface Library")
class ULifeCycleLibrary : public UBlueprintFunctionLibrary
{

	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Meta = (DefaultToSelf = "Target", AdvancedDisplay = "Parameters, bSkipLoad, bSkipValidate"))
	static void StartLifecycle(UObject* Target, const FInstancedStruct& Parameters, const bool bSkipLoad = true, const bool bSkipValidate = true);

	UFUNCTION(BlueprintCallable, Meta = (DefaultToSelf = "Target", AdvancedDisplay = "Parameters, bSkipLoad"))
	static void StartLifecycleWithLoader(UObject* Target, const FInstancedStruct& Parameters, const bool bSkipValidate = true);

	UFUNCTION(BlueprintCallable, Meta = (DefaultToSelf = "Target", AdvancedDisplay = "Parameters, bSkipLoad"))
	static void StartLifecycleWithValidation(UObject* Target, const FInstancedStruct& Parameters, const bool bSkipLoad = true);

	UFUNCTION(BlueprintCallable, Meta = (DefaultToSelf = "Target"))
	static void Loaded(UObject* Target);

};

