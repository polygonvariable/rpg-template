// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "NativeGameplayTags.h"

// Project Headers
#include "AbilityMacro.h"

// Generated Headers
#include "DefenceAttributeSet.generated.h"


/**
 * 
 */
UCLASS()
class UDefenceAttributeSet : public UAttributeSet
{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData PhysicalDefence;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData MagicalDefence;
	

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

public:

	ATTRIBUTE_ACCESSORS(UDefenceAttributeSet, PhysicalDefence)
	ATTRIBUTE_ACCESSORS(UDefenceAttributeSet, MagicalDefence)

};

