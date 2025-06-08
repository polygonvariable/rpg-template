// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayEffect.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"

// Generated Headers
#include "AbilitySystemLibrary.generated.h"



/**
 * 
 */
UCLASS()
class RENABILITY_API UAbilitySystemLibrary : public UBlueprintFunctionLibrary
{

	GENERATED_BODY()

public:

	static void ApplyGameplayEffectToTarget(AActor* Target, AActor* Caster, AActor* Causer, TSubclassOf<UGameplayEffect> EffectClass, int Level = 1, TFunctionRef<void(FGameplayEffectContextHandle&)> CustomizeEffectContext = [](FGameplayEffectContextHandle& Context) {});

};

