// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"

// Project Headers
#include "StampedEvent/StampedEventComponent.h"
#include "StampedEvent/StampedEventTypes.h"

// Generated Headers
#include "StampedEventCooldownComponent.generated.h"


/**
 *
 */
UCLASS(Blueprintable, ClassGroup=(Custom), Meta=(BlueprintSpawnableComponent), DisplayName="Stamped Event Cooldown Component")
class RENINTERACT_API UStampedEventCooldownComponent : public UStampedEventComponent
{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "StampChangeCooldown Component|Item")
	FTimespan CooldownTime;


	UPROPERTY(EditAnywhere, Category = "StampChangeCooldown Component|Item")
	bool bOnlyOnce = false;

public:
    
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStampedEventCooldownStatus, EStampedEventCooldownStatus, Status);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Stamped Event Cooldown Component|Event Dispatcher")
	FOnStampedEventCooldownStatus OnStampedEventCooldownStatus;

protected:
    
	virtual void ActivateStage_Implementation() override;
		
};