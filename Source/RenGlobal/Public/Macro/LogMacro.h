// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogInventorySubsystem, Log, All);


template <typename T>
FString GetClassName(const T* Object)
{
    return Object ? Object->GetClass()->GetName() : TEXT("UnknownClass");
}

#define LOG_INFO(Object, Category, Format, ...) \
    UE_LOG(Category, Log, TEXT("[%s::%s] " Format), *GetClassName(Object), *FString(__FUNCTION__), ##__VA_ARGS__) \

#define LOG_WARNING(Object, Category, Format, ...) \
    UE_LOG(Category, Warning, TEXT("[%s::%s] " Format), *GetClassName(Object), *FString(__FUNCTION__), ##__VA_ARGS__)

#define LOG_ERROR(Object, Category, Format, ...) \
    UE_LOG(Category, Error, TEXT("[%s::%s] " Format), *GetClassName(Object), *FString(__FUNCTION__), ##__VA_ARGS__)

#define PRINT(Text, Color) \
    if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, Color, Text)

