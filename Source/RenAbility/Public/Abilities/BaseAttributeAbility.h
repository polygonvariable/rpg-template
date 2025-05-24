// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "InstancedStruct.h"
#include "Abilities/GameplayAbility.h"
#include "AttributeSet.h"
#include "Components/ActorComponent.h"

// Project Headers
#include "RenGlobal/Public/Macro/LogMacro.h"

// Generated Headers
#include "BaseAttributeAbility.generated.h"

// Forward Declarations



/**
 * TODO
 * This will be removed as custom ULevelMagnitudeCalculation class added
 * to override the new max attribute values. which doesnt require
 * long running ability or effect.
 *
 */
UCLASS()
class UBaseAttributeAbility : public UGameplayAbility
{

	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttribute LevelAttribute;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> TargetEffectClass;

	UPROPERTY(BlueprintReadOnly)
	FActiveGameplayEffectHandle ActiveEffectHandle;



	virtual void OnLevelAttributeChanged(const FOnAttributeChangeData& Data);

public:

	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

};


/**
 *
 */
//UCLASS(ClassGroup = (Custom), Meta = (BlueprintSpawnableComponent))
//class UAbilityObserverComponent : public UActorComponent
//{
//
//	GENERATED_BODY()
//
//public:
//
//	UAbilityObserverComponent();
//
//
//	UPROPERTY(BlueprintReadOnly)
//	TObjectPtr<UAbilitySystemComponent> AbilityComponent;
//
//	UPROPERTY(EditAnywhere, BlueprintReadOnly)
//	FGameplayAttribute LevelAttribute;
//
//	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
//	TSubclassOf<UGameplayEffect> TargetEffectClass;
//
//	UPROPERTY(BlueprintReadOnly)
//	FActiveGameplayEffectHandle ActiveEffectHandle;
//
//	UFUNCTION(BlueprintCallable)
//	void RegisterObserver();
//
//	virtual void OnLevelAttributeChanged(const FOnAttributeChangeData& Data);
//
//};


