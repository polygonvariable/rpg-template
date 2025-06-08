// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Ability/RGameplayAbility.h"

// Project Headers



FGameplayTagContainer URGameplayAbility::GetDynamicTags(bool& bSuccess) const
{
	const FGameplayAbilitySpec* Spec = GetCurrentAbilitySpec();

	if (!Spec)
	{
		bSuccess = false;
		return FGameplayTagContainer();
	}

	bSuccess = true;
	return Spec->DynamicAbilityTags;
}

