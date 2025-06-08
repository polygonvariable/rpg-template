// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Component/RAbilitySystemComponent.h"

// Project Headers
#include "RenGlobal/Public/Macro/LogMacro.h"


FGameplayAbilitySpecHandle URAbilitySystemComponent::GiveAbilityWithDynamicTags(TSubclassOf<UGameplayAbility> AbilityClass, int Level, int InputID, const FGameplayTagContainer& DynamicTags)
{
	if (!IsValid(AbilityClass))
	{
		return FGameplayAbilitySpecHandle();
	}

	FGameplayAbilitySpec AbilitySpec = BuildAbilitySpecFromClass(AbilityClass, Level, InputID);
	if (!IsValid(AbilitySpec.Ability))
	{
		return FGameplayAbilitySpecHandle(); 
	}

	AbilitySpec.DynamicAbilityTags.AppendTags(DynamicTags);

	return GiveAbility(AbilitySpec);
}

void URAbilitySystemComponent::AddAggregatedActor(const FGameplayAttribute& Attribute, AActor* Actor)
{
	if (!IsValid(Actor)) return;

	TSet<TWeakObjectPtr<AActor>>& Actors = AggregatedActors.FindOrAdd(Attribute);
	Actors.Add(Actor);

	OnAggregatedRefresh.Broadcast();
	OnAggregatedActorAdded.Broadcast(Actor);
}

void URAbilitySystemComponent::RemoveAggregatedActor(const FGameplayAttribute& Attribute, AActor* Actor)
{
	if (!IsValid(Actor)) return;

	TSet<TWeakObjectPtr<AActor>>& Actors = AggregatedActors.FindOrAdd(Attribute);
	Actors.Remove(Actor);

	OnAggregatedRefresh.Broadcast();
	OnAggregatedActorRemoved.Broadcast(Actor);
	
}

float URAbilitySystemComponent::GetAggregatedNumericAttribute(const FGameplayAttribute& Attribute)
{
	float Value = GetNumericAttribute(Attribute);

	const TSet<TWeakObjectPtr<AActor>>& Actors = AggregatedActors.FindRef(Attribute);

	for (TWeakObjectPtr<AActor> Actor : Actors)
	{
		if (!Actor.IsValid()) continue;
		if (UAbilitySystemComponent* ASC = Actor->GetComponentByClass<UAbilitySystemComponent>())
		{
			Value += ASC->GetNumericAttribute(Attribute);
		}
	}

	return Value;
}

