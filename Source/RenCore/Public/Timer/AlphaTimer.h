// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"

// Project Headers
#include "Timer/Timer.h"

// Generated Headers
#include "AlphaTimer.generated.h"


/**
 *
 */
UCLASS(Blueprintable)
class RENCORE_API UAlphaTimer : public UTimer
{

	GENERATED_BODY()

public:

	UAlphaTimer();
	
	virtual void StartTimer_Implementation(const float InTime = 1.0f) override;
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TickFrequency = 0.1f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Runtime")
	int TickIncrement = 0;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Runtime")
	int TickLimit = 0;


	virtual void HandleTick_Implementation() override;

public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAlphaTick, float, Alpha);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Event Dispatcher")
	FOnAlphaTick OnAlphaTick;

};

