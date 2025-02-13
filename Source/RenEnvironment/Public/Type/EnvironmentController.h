// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"
#include "InstancedStruct.h"

// Project Headers
#include "RenCore/Public/Priority/PrioritySystem.h"
#include "EnvironmentActor.h"

// Generated Headers
#include "EnvironmentController.generated.h"


/**
 * 
 */
UCLASS()
class RENENVIRONMENT_API UEnvironmentController : public UPrioritySystem
{

	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<AEnvironmentActor> EnvironmentActor;

protected:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected))
	void SetTimer(const float Duration = 5.0f, const float Interval = 1.0f);
	virtual void SetTimer_Implementation(const float Duration = 5.0f, const float Interval = 1.0f);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected))
	void OnTransitioned(const float DeltaTime, const float Alpha);
	virtual void OnTransitioned_Implementation(const float DeltaTime, const float Alpha);

protected:

	virtual void OnItemAdded_Implementation(FInstancedStruct Item) override;

};

