// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

// Project Headers
#include "RenCore/Public/LifeCycle/LifeCycleInterface.h"
#include "StampedEvent/StampedEventTypes.h"

// Generated Headers
#include "StampedEventComponent.generated.h"

// Forward Declarations
class UStorage;


/**
 *
 */
UCLASS(Blueprintable, ClassGroup=(Custom), Meta=(BlueprintSpawnableComponent), DisplayName="Stamped Event Component")
class RENINTERACT_API UStampedEventComponent : public UActorComponent, public ILifeCycleInterface
{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Stamped Event Component|Item")
	FGuid UUID;


	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Stamped Event Component|Runtime")
	TObjectPtr<UStorage> Storage;

protected:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Stamped Event Component|Action")
	void AddChange(const bool Force = false);
	virtual void AddChange_Implementation(const bool Force = false);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Stamped Event Component|Action")
	void RemoveChange();
	virtual void RemoveChange_Implementation();


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintPure), Category = "Stamped Event Component|Action")
	bool HasChanged();
	virtual bool HasChanged_Implementation();


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Stamped Event Component|Action")
	bool GetEventDate(FDateTime& EventDate);
	virtual bool GetEventDate_Implementation(FDateTime& EventDate);
    
public:
    
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStampedEventStatus, EStampedEventStatus, Status);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Stamped Event Component|Event Dispatcher")
	FOnStampedEventStatus OnStampedEventStatus;

protected:
    
	virtual void BeginStage_Implementation(const FInstancedStruct Parameters) override;
	virtual bool ValidateStage_Implementation() override;
	virtual void ActivateStage_Implementation() override;
		
};