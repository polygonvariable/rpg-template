// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Attributes/DefenceAttributeSet.h"

// Engine Headers
#include "GameplayEffectExtension.h"
#include "GameplayEffect.h"

// Project Headers
#include "RenGlobal/Public/Macro/LogMacro.h"
#include "RenCore/Public/Tag/GameTags.h"



void UDefenceAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetPhysicalDefenceAttribute())
	{
		NewValue = FMath::Max(NewValue, 0.0f);
	}
}

void UDefenceAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}

