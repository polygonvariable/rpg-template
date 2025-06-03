// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

// Generated Headers
#include "AbilitySystemLibrary.generated.h"



/**
 * 
 */
UCLASS()
class RENABILITY_API UAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	static FActiveGameplayEffectHandle ApplyGameplayEffectSpecToTarget(TSubclassOf<UGameplayEffect> EffectClass, AActor* Target, AActor* Causer);

};