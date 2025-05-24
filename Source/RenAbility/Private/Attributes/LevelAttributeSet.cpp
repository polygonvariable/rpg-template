// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Attributes/LevelAttributeSet.h"

// Engine Headers
#include "GameplayEffectExtension.h"
#include "GameplayEffect.h"
#include "NativeGameplayTags.h"
#include "Kismet/GameplayStatics.h"
#include "InstancedStruct.h"

// Project Headers
#include "RenGlobal/Public/Macro/LogMacro.h"
#include "RenCore/Public/Tag/GameTags.h"



//void ULevelAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
//{
//	Super::PreAttributeChange(Attribute, NewValue);
//
//	if (Attribute == GetLevelAttribute())
//	{
//		NewValue = FMath::Clamp(NewValue, 0.0f, GetLevel());
//	}
//	else if (Attribute == GetLevelMaxAttribute())
//	{
//		NewValue = FMath::Clamp(NewValue, 0.0f, FLT_MAX);
//	}
//	else if (Attribute == GetExperienceAttribute())
//	{
//		NewValue = FMath::Clamp(NewValue, 0.0f, GetExperienceMax());
//	}
//	else if (Attribute == GetExperienceMaxAttribute())
//	{
//		NewValue = FMath::Clamp(NewValue, 0.0f, FLT_MAX);
//	}
//	else if (Attribute == GetRankAttribute())
//	{
//		NewValue = FMath::Clamp(NewValue, 0.0f, GetRankMax());
//	}
//	else if (Attribute == GetRankMaxAttribute())
//	{
//		NewValue = FMath::Clamp(NewValue, 0.0f, FLT_MAX);
//	}
//}
