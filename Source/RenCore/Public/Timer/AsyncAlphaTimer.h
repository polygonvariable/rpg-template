// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsyncAlphaTimer.generated.h"


/**
 * 
 */
UCLASS(BlueprintType, Meta = (ExposedAsyncProxy = AsyncTask))
class RENCORE_API UAsyncAlphaTimer : public UBlueprintAsyncActionBase
{

	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, DisplayName = "Async Alpha Timer", Meta = (WorldContext = "InWorldContextObject", BlueprintInternalUseOnly = "true"))
	static UAsyncAlphaTimer* Start(const UObject* InWorldContextObject, const float InTime = 1.0f, const float InTickFrequency = 0.1f);

	virtual void Activate() override;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStart, float, Alpha);
	UPROPERTY(BlueprintAssignable, DisplayName = "Start")
	FOnStart OnStart;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTick, float, Alpha);
	UPROPERTY(BlueprintAssignable, DisplayName = "Tick")
	FOnTick OnTick;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnComplete, float, Alpha);
	UPROPERTY(BlueprintAssignable, DisplayName = "Complete")
	FOnComplete OnComplete;

	UFUNCTION(BlueprintCallable)
	void EndTask();

private:

	FTimerHandle TimerHandle;
    float Time;
	float TickFrequency;
	const UObject* WorldContextObject;
	
	int TickIncrement = 0;
	int TickLimit = 0;

	void HandleOnStart();
	void HandleOnTick();
	void HandleOnComplete();

};
