// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"

// Log Categories
RENGLOBAL_API DECLARE_LOG_CATEGORY_EXTERN(LogInventorySubsystem, Log, All);
RENGLOBAL_API DECLARE_LOG_CATEGORY_EXTERN(LogInventoryWidget, Log, All);




template <typename T>
FString GetClassName(const T* Object)
{
    return Object ? Object->GetClass()->GetName() : TEXT("UnknownClass");
}

#define LOG_INFO(Object, Category, Text, ...) \
    { \
        const FString __Message__ = FString::Printf(TEXT("[%s::%s] " Text), *GetClassName(Object), *FString(__FUNCTION__), ##__VA_ARGS__); \
        UE_LOG(Category, Log, TEXT("%s"), *__Message__) \
        PRINT(__Message__, FColor::Green) \
    }

#define LOG_WARNING(Object, Category, Text, ...) \
    { \
        const FString __Message__ = FString::Printf(TEXT("[%s::%s] " Text), *GetClassName(Object), *FString(__FUNCTION__), ##__VA_ARGS__); \
        UE_LOG(Category, Warning, TEXT("%s"), *__Message__) \
        PRINT(__Message__, FColor::Orange) \
    }

#define LOG_ERROR(Object, Category, Text, ...) \
    { \
        const FString __Message__ = FString::Printf(TEXT("[%s::%s] " Text), *GetClassName(Object), *FString(__FUNCTION__), ##__VA_ARGS__); \
        UE_LOG(Category, Error, TEXT("%s"), *__Message__) \
        PRINT(__Message__, FColor::Red) \
    }

#define PRINT(Text, Color) \
    if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, Color, Text);

