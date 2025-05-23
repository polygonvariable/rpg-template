// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Attributes/HealthAttributeSet.h"

// Engine Headers
#include "GameplayEffectExtension.h"
#include "GameplayEffect.h"

// Project Headers
#include "RenGlobal/Public/Macro/LogMacro.h"
#include "RenCore/Public/Tag/GameTags.h"


//FGameplayEffectAttributeCaptureDefinition UHealthAttributeSet::GetPhysicalDefenseAttributeCaptureDefinition()
//{
//	return FGameplayEffectAttributeCaptureDefinition();
//}

bool UHealthAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	if (!Super::PreGameplayEffectExecute(Data))
	{
		return false;
	}

	//if (UAbilitySystemComponent* AbilityComponent = GetOwningAbilitySystemComponent())
	//{
	//	FGameplayTagContainer Tags;
	//	Tags.AddTag(TAG_Attribute_State_Life_Immortal);
	//	return !AbilityComponent->HasAnyMatchingGameplayTags(Tags);
	//}
	//return false;

	return true;
}

void UHealthAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetHealthMax());
	}
	else if (Attribute == GetHealthMaxAttribute())
	{
		NewValue = FMath::Max(NewValue, 0.0f);
	}
}

void UHealthAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		FGameplayEffectSpec Spec = Data.EffectSpec;
		FGameplayTagContainer AssetTags;
		Data.EffectSpec.GetAllAssetTags(AssetTags);

		if (AssetTags.HasTag(TAG_Effect_Damage_Magical))
		{
			PRINT_WARNING(LogTemp, 5.0f, TEXT("Magical Damage"));
		}
		else if(AssetTags.HasTag(TAG_Effect_Damage_Physical))
		{
			PRINT_WARNING(LogTemp, 5.0f, TEXT("Physical Damage"));
		}
		else
		{
			PRINT_WARNING(LogTemp, 5.0f, TEXT("Unknown Damage"));
		}

		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetHealthMax()));

		if (UAbilitySystemComponent* AbilityComponent = GetOwningAbilitySystemComponent())
		{
			/*FGameplayTagContainer AliveTags;
			AliveTags.AddTag(TAG_Attribute_State_Life_Alive);
			FGameplayTagContainer DeathTags;
			DeathTags.AddTag(TAG_Attribute_State_Life_Death);*/

			if (GetHealth() <= 0.0f)
			{
				AbilityComponent->AddLooseGameplayTag(TAG_Attribute_State_Life_Death);
				AbilityComponent->RemoveLooseGameplayTag(TAG_Attribute_State_Life_Alive);
				PRINT_INFO(LogTemp, 5.0f, TEXT("Actor Died"));
			}

			/*else if (GetHealth() > 0.0f && AbilityComponent->HasAnyMatchingGameplayTags(DeathTags))
			{
				AbilityComponent->AddLooseGameplayTag(TAG_Attribute_State_Life_Alive);
				AbilityComponent->RemoveLooseGameplayTag(TAG_Attribute_State_Life_Death);
			}
			if (GetHealth() <= 0.0f && AbilityComponent->HasAnyMatchingGameplayTags(AliveTags))
			{
				AbilityComponent->AddLooseGameplayTag(TAG_Attribute_State_Life_Death);
				AbilityComponent->RemoveLooseGameplayTag(TAG_Attribute_State_Life_Alive);
			}
			else if(GetHealth() > 0.0f && AbilityComponent->HasAnyMatchingGameplayTags(DeathTags))
			{
				AbilityComponent->AddLooseGameplayTag(TAG_Attribute_State_Life_Alive);
				AbilityComponent->RemoveLooseGameplayTag(TAG_Attribute_State_Life_Death);
			}*/
		}
	}
}

