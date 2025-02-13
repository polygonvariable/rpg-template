// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsyncTimer.generated.h"


/**
 * 
 */
UCLASS(BlueprintType, Meta = (ExposedAsyncProxy = AsyncTask))
class RENCORE_API UAsyncTimer : public UBlueprintAsyncActionBase
{

	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, DisplayName = "Async Timer", Meta = (WorldContext = "InWorldContextObject", BlueprintInternalUseOnly = "true"))
	static UAsyncTimer* Start(const UObject* InWorldContextObject, const float InTime = 10.0f, const bool bInLooping = false);

	virtual void Activate() override;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStart);
	UPROPERTY(BlueprintAssignable, DisplayName = "Start")
	FOnStart OnStart;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnComplete);
	UPROPERTY(BlueprintAssignable, DisplayName = "Complete")
	FOnComplete OnComplete;

	UFUNCTION(BlueprintCallable)
	void EndTask();

private:

	FTimerHandle TimerHandle;
    float Time;
    bool bLooping = false;
	const UObject* WorldContextObject;

	void HandleOnStart();
	void HandleOnComplete();

};
