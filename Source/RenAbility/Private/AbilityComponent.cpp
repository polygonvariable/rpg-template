// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "AbilityComponent.h"



void UAbilityComponent::AddAggregatedActor(const FGameplayAttribute& Attribute, AActor* Actor)
{
	if (!IsValid(Actor)) return;

	TSet<TWeakObjectPtr<AActor>>& Actors = AggregatedActors.FindOrAdd(Attribute);
	Actors.Add(Actor);

	OnAggregatedRefresh.Broadcast();
	OnAggregatedActorAdded.Broadcast(Actor);
}

void UAbilityComponent::RemoveAggregatedActor(const FGameplayAttribute& Attribute, AActor* Actor)
{
	if (!IsValid(Actor)) return;

	TSet<TWeakObjectPtr<AActor>>& Actors = AggregatedActors.FindOrAdd(Attribute);
	Actors.Remove(Actor);

	OnAggregatedRefresh.Broadcast();
	OnAggregatedActorRemoved.Broadcast(Actor);
}


float UAbilityComponent::GetAggregatedNumericAttribute(const FGameplayAttribute& Attribute)
{
	float Value = GetNumericAttribute(Attribute);

	if (TSet<TWeakObjectPtr<AActor>>* Actors = AggregatedActors.Find(Attribute))
	{
		for (TWeakObjectPtr<AActor> Actor : *Actors)
		{
			if (!Actor.IsValid()) continue;
			if (UAbilitySystemComponent* ASC = Actor->GetComponentByClass<UAbilitySystemComponent>())
			{
				Value += ASC->GetNumericAttribute(Attribute);
			}
		}
	}

	return Value;
}



