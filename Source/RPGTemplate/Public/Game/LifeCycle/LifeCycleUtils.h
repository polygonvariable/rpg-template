#pragma once

#include "CoreMinimal.h"
#include "InstancedStruct.h"
#include "UObject/Interface.h"
#include "LifeCycleUtils.generated.h"


UINTERFACE(MinimalAPI, Blueprintable, DisplayName = "LifeCycle Interface")
class ULifeCycleInterface : public UInterface
{
	GENERATED_BODY()
};

class ILifeCycleInterface
{

	GENERATED_BODY()

public:

	bool bStarted = false;

	void StartLifecycle(UObject* Target, FInstancedStruct Parameters, bool bSkipLoad = true, bool bSkipValidate = true)
	{
		if (!Target) {
			UE_LOG(LogTemp, Warning, TEXT("Invalid Target"));
			return;
		}

		if (bStarted) {
			UE_LOG(LogTemp, Warning, TEXT("Lifecycle already started"));
			return;
		}

		Execute_BeginStage(Target, Parameters);
		bStarted = true;

		if (!bSkipLoad) {
			Execute_LoadStage(Target);
		}
		else {
			if (!bSkipValidate && Execute_ValidateStage(Target)) {
				Execute_ActivateStage(Target);
			}
			else if (bSkipValidate) {
				Execute_ActivateStage(Target);
			}
		}
	}
	void Loaded(UObject* Target) {
		if (!bStarted) {
			UE_LOG(LogTemp, Warning, TEXT("Lifecycle not started"));
			return;
		}
		if (!Target) {
			if (Execute_ValidateStage(Target)) {
				Execute_ActivateStage(Target);
			}
		}
	}

protected:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Meta = (ForceAsFunction, BlueprintProtected), Category = "LifeCycle Interface")
	void BeginStage(FInstancedStruct Parameters);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Meta = (ForceAsFunction, BlueprintProtected), Category = "LifeCycle Interface")
	void LoadStage();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Meta = (ForceAsFunction, BlueprintProtected), Category = "LifeCycle Interface")
	bool ValidateStage();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Meta = (ForceAsFunction, BlueprintProtected), Category = "LifeCycle Interface")
	void ActivateStage();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Meta = (ForceAsFunction, BlueprintProtected), Category = "LifeCycle Interface")
	void EndStage(const EEndPlayReason::Type EndPlayReason);

};

UCLASS(MinimalAPI)
class ULifeCycleLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (DefaultToSelf = "Target", AdvancedDisplay = "bSkipLoad, bSkipValidate"), Category = "LifeCycle Interface Library")
	static void StartLifecycle(UObject* Target, FInstancedStruct Parameters, bool bSkipLoad = true, bool bSkipValidate = true) {

		if (ILifeCycleInterface* Interface = Cast<ILifeCycleInterface>(Target))
		{
			Interface->StartLifecycle(Target, Parameters, bSkipLoad, bSkipValidate);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Target does not implement ILifeCycleInterface"));
		}

	}

	UFUNCTION(BlueprintCallable, meta = (DefaultToSelf = "Target", AdvancedDisplay = "bSkipLoad"), Category = "LifeCycle Interface Library")
	static void StartLifecycleWithLoader(UObject* Target, FInstancedStruct Parameters, bool bSkipValidate = true) {
		StartLifecycle(Target, Parameters, false, bSkipValidate);
	}

	UFUNCTION(BlueprintCallable, meta = (DefaultToSelf = "Target", AdvancedDisplay = "bSkipLoad"), Category = "LifeCycle Interface Library")
	static void StartLifecycleWithValidation(UObject* Target, FInstancedStruct Parameters, bool bSkipLoad = true) {
		StartLifecycle(Target, Parameters, bSkipLoad, true);
	}

	UFUNCTION(BlueprintCallable, meta = (DefaultToSelf = "Target"), Category = "LifeCycle Interface Library")
	static void Loaded(UObject* Target) {

		if (ILifeCycleInterface* Interface = Cast<ILifeCycleInterface>(Target))
		{
			Interface->Loaded(Target);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Target does not implement ILifeCycleInterface"));
		}

	}

};