// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"

// Project Headers

// Generated Headers
#include "AbilityComponent.generated.h"

// Forward Declarations


/**
 * 
 */
UCLASS()
class RENABILITY_API UAbilityComponent : public UAbilitySystemComponent
{

	GENERATED_BODY()

public:

	UFUNCTION()
	void AddAggregatedActor(const FGameplayAttribute& Attribute, AActor* Actor);

	UFUNCTION()
	void RemoveAggregatedActor(const FGameplayAttribute& Attribute, AActor* Actor);

	UFUNCTION()
	float GetAggregatedNumericAttribute(const FGameplayAttribute& Attribute);

protected:

	TMap<FGameplayAttribute, TSet<TWeakObjectPtr<AActor>>> AggregatedActors;

public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAggregatedActorAdded, AActor*, Actor);
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnAggregatedActorAdded OnAggregatedActorAdded;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAggregatedActorRemoved, AActor*, Actor);
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnAggregatedActorRemoved OnAggregatedActorRemoved;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAggregatedRefresh);
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnAggregatedRefresh OnAggregatedRefresh;

};