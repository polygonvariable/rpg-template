// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Abilities/BaseAttributeAbility.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"

// Engine Headers
#include "Kismet/GameplayStatics.h"

// Project Headers
#include "RenGlobal/Public/Macro/LogMacro.h"
#include "RenCore/Public/Tag/GameTags.h"



void UBaseAttributeAbility::OnLevelAttributeChanged(const FOnAttributeChangeData& Data)
{
	PRINT_INFO(LogTemp, 2.0f, TEXT("Level attribute's value changed"));

	if (UAbilitySystemComponent* AbilityComponent = GetAvatarActorFromActorInfo()->FindComponentByClass<UAbilitySystemComponent>())
	{
		if (ActiveEffectHandle.IsValid())
		{
			int NewLevel = FMath::RoundToInt(Data.NewValue);
			AbilityComponent->SetActiveGameplayEffectLevel(ActiveEffectHandle, NewLevel);
		}
		else
		{
			FGameplayAbilitySpecHandle SpecHandle = GetCurrentAbilitySpecHandle();
			if (SpecHandle.IsValid())
			{
				FGameplayAbilityActorInfo ActivationInfo = GetActorInfo();
				EndAbility(SpecHandle, &ActivationInfo, FGameplayAbilityActivationInfo(), false, true);
			}
		}
	}
}



bool UBaseAttributeAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}
	return IsValid(TargetEffectClass) && LevelAttribute.IsValid();
}

void UBaseAttributeAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!IsValid(TargetEffectClass))
	{
		PRINT_ERROR(LogTemp, 5.0f, TEXT("TargetEffectClass is not valid"));
		return;
	}

	if (UAbilitySystemComponent* AbilityComponent = GetAbilitySystemComponentFromActorInfo())
	{
		FGameplayEffectContextHandle EffectContext = AbilityComponent->MakeEffectContext();
		UGameplayEffect* GameplayEffect = TargetEffectClass->GetDefaultObject<UGameplayEffect>();
		
		if (!IsValid(GameplayEffect) || GameplayEffect->DurationPolicy != EGameplayEffectDurationType::Infinite)
		{
			PRINT_ERROR(LogTemp, 5.0f, TEXT("TargetEffectClass instance is not valid or duration policy is not infinite"));
			EndAbility(Handle, ActorInfo, ActivationInfo, false, true);
			return;
		}

		float Level = GetAbilityLevel();
		
		ActiveEffectHandle = AbilityComponent->ApplyGameplayEffectToSelf(GameplayEffect, Level, EffectContext);
		if (!ActiveEffectHandle.IsValid() || !LevelAttribute.IsValid())
		{
			PRINT_ERROR(LogTemp, 5.0f, TEXT("TargetEffectClass handler or level attribute is not valid"));
			EndAbility(Handle, ActorInfo, ActivationInfo, false, true);
			return;
		}

		PRINT_INFO(LogTemp, 2.0f, TEXT("TargetEffectClass applied"));

		AbilityComponent->GetGameplayAttributeValueChangeDelegate(LevelAttribute).AddUObject(this, &UBaseAttributeAbility::OnLevelAttributeChanged);
		AbilityComponent->AddLooseGameplayTag(TAG_Attribute_Base);
	}
}

void UBaseAttributeAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (UAbilitySystemComponent* AbilityComponent = GetAbilitySystemComponentFromActorInfo())
	{
		if (ActiveEffectHandle.IsValid())
		{
			AbilityComponent->RemoveActiveGameplayEffect(ActiveEffectHandle);
		}
		AbilityComponent->GetGameplayAttributeValueChangeDelegate(LevelAttribute).RemoveAll(this);
		AbilityComponent->RemoveLooseGameplayTag(TAG_Attribute_Base);
	}

	PRINT_INFO(LogTemp, 2.0f, TEXT("TargetEffectClass removed"));

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}



//UAbilityObserverComponent::UAbilityObserverComponent()
//{
//	PrimaryComponentTick.bCanEverTick = false;
//	AbilityComponent = GetOwner()->GetComponentByClass<UAbilitySystemComponent>();
//}
//void UAbilityObserverComponent::RegisterObserver()
//{
//	AbilityComponent->GetGameplayAttributeValueChangeDelegate(LevelAttribute).AddUObject(this, &UAbilityObserverComponent::OnLevelAttributeChanged);
//	AbilityComponent->AddLooseGameplayTag(TAG_Attribute_Base);
//}
//void UAbilityObserverComponent::OnLevelAttributeChanged(const FOnAttributeChangeData& Data)
//{
//}

