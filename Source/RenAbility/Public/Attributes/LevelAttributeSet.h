// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"

// Project Headers
#include "AbilityMacro.h"

// Generated Headers
#include "LevelAttributeSet.generated.h"



/**
 *
 */
UCLASS()
class ULevelAttributeSet : public UAttributeSet
{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Level;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData LevelMax;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Rank;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData RankMax;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Experience;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData ExperienceMax;

public:

	ATTRIBUTE_ACCESSORS(ULevelAttributeSet, Level)
	ATTRIBUTE_ACCESSORS(ULevelAttributeSet, LevelMax)
	ATTRIBUTE_ACCESSORS(ULevelAttributeSet, Rank)
	ATTRIBUTE_ACCESSORS(ULevelAttributeSet, RankMax)
	ATTRIBUTE_ACCESSORS(ULevelAttributeSet, Experience)
	ATTRIBUTE_ACCESSORS(ULevelAttributeSet, ExperienceMax)

};

