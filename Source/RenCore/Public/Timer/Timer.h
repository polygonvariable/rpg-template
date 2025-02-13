// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"

// Generated Headers
#include "Timer.generated.h"


/**
 *
 */
UCLASS(Blueprintable)
class RENCORE_API UTimer : public UObject
{

	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Action")
	void StartTimer(const float InTime = 1.0f);
	virtual void StartTimer_Implementation(const float InTime = 1.0f);
	

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Action")
	void StopTimer();
	virtual void StopTimer_Implementation();
	

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Action")
	void RestartTimer(const float InTime = 1.0f);
	virtual void RestartTimer_Implementation(const float InTime = 1.0f);


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bLooping = false;

protected:

	UPROPERTY(BlueprintReadWrite)
	FTimerHandle TimerHandle;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Runtime")
	float DeltaTime = 0.0f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Runtime")
	bool bIsActive = false;


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Handler")
	void HandleTick();
	virtual void HandleTick_Implementation();

public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTicked);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Event Dispatcher")
	FOnTicked OnTicked;

};

