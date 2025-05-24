// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"

// Project Headers
#include "AbilityMacro.h"

// Generated Headers
#include "HealthAttributeSet.generated.h"


/**
 * 
 */
UCLASS()
class UHealthAttributeSet : public UAttributeSet
{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData HealthMax;

	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

public:

	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, Health)
	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, HealthMax)

};

