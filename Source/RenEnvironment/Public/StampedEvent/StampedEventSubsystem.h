// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"

// Project Headers
#include "RenCore/Public/Subsystem/RenGameInstanceSubsystem.h"
#include "StampedEvent/StampedEventType.h"

// Generated Headers
#include "StampedEventSubsystem.generated.h"

// Forward Declarations
class UStorage;


/**
 *
 */
UCLASS(DisplayName = "Stamped Event Subsystem")
class RENENVIRONMENT_API UStampedEventSubsystem : public URenGameInstanceSubsystem
{

	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Stamped Event Subsystem|Action")
	bool AddChange(const FGuid Id, const bool bForceAdd = false);
	virtual bool AddChange_Implementation(const FGuid Id, const bool bForceAdd = false);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Stamped Event Subsystem|Action")
	bool RemoveChange(const FGuid Id);
	virtual bool RemoveChange_Implementation(const FGuid Id);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, BlueprintPure, Meta = (ForceAsFunction), Category = "Stamped Event Subsystem|Action")
	bool HasChanged(const FGuid Id);
	virtual bool HasChanged_Implementation(const FGuid Id);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Stamped Event Subsystem|Action")
	bool GetEventDate(const FGuid Id, FDateTime& EventDate);
	virtual bool GetEventDate_Implementation(const FGuid Id, FDateTime& EventDate);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, BlueprintPure, Meta = (ForceAsFunction), Category = "Stamped Event Subsystem|Action")
	EStampedEventStatus GetEventStatus(const FGuid Id);
	virtual EStampedEventStatus GetEventStatus_Implementation(const FGuid Id);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, BlueprintPure, Meta = (ForceAsFunction), Category = "Stamped Event Subsystem|Action")
	EStampedEventCooldownStatus GetEventCooldownStatus(const FGuid Id, const bool bIsOnlyOnce, const FTimespan CooldownTime);
	virtual EStampedEventCooldownStatus GetEventCooldownStatus_Implementation(const FGuid Id, const bool bIsOnlyOnce, const FTimespan CooldownTime);

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Stamped Event Subsystem|Runtime")
	UStorage* Storage;

public:

	virtual void PostInitialize_Implementation() override;

};

