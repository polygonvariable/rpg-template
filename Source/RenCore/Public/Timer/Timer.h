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
	void StartTimer(const float InTickInterval = 1.0f, const int InTickLimit = 10, const bool bPreserveTime = false);
	virtual void StartTimer_Implementation(const float InTickInterval = 1.0f, const int InTickLimit = 10, const bool bPreserveTime = false);
	

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Action")
	void StopTimer();
	virtual void StopTimer_Implementation();
	

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Action")
	void RestartTimer(const float InTickInterval = 1.0f, const int InTickLimit = 10);
	virtual void RestartTimer_Implementation(const float InTickInterval = 1.0f, const int InTickLimit = 10);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Action")
	void SetTickInterval(const float InTickInterval = 1.0f);
	virtual void SetTickInterval_Implementation(const float InTickInterval = 1.0f);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Property")
	const bool bIsActive();
	virtual const bool bIsActive_Implementation();


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Property")
	const float GetNormalizedAlpha();
	const virtual float GetNormalizedAlpha_Implementation();

protected:

	UPROPERTY(BlueprintReadWrite)
	FTimerHandle TimerHandle;


	UPROPERTY(BlueprintReadWrite, Category = "Property")
	int TickLimit = 0;


	UPROPERTY(BlueprintReadWrite, Category = "Property")
	float TickInterval = 0.0f;


	UPROPERTY(BlueprintReadWrite, Category = "Runtime")
	int TickCount = 0;


	UPROPERTY(BlueprintReadWrite, Category = "Runtime")
	float Time = 0.0f;


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Handler")
	void HandleTick();
	virtual void HandleTick_Implementation();


public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStarted);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Event Dispatcher")
	FOnStarted OnStarted;


	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTick, float, CurrentTime, float, TotalTime);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Event Dispatcher")
	FOnTick OnTick;


	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCompleted);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Event Dispatcher")
	FOnCompleted OnCompleted;

};

