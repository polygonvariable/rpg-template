// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Attributes/DamageAttributeSet.h"

// Engine Headers
#include "GameplayEffectExtension.h"
#include "GameplayEffect.h"

// Project Headers
#include "RenGlobal/Public/Macro/LogMacro.h"
#include "RenCore/Public/Tag/GameTags.h"



void UDamageAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void UDamageAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}

