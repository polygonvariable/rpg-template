// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

template <typename T>
FString GetClassName(const T* Object)
{
    return Object ? Object->GetClass()->GetName() : TEXT("UnknownClass");
}

#define LOG_INFO(Object, Category, Format, ...) \
    UE_LOG(Category, Display, TEXT("[%s::%s] " Format), *GetClassName(Object), *FString(__FUNCTION__), ##__VA_ARGS__) \

#define LOG_WARNING(Object, Category, Format, ...) \
    UE_LOG(Category, Warning, TEXT("[%s::%s] " Format), *GetClassName(Object), *FString(__FUNCTION__), ##__VA_ARGS__)

#define LOG_ERROR(Object, Category, Format, ...) \
    UE_LOG(Category, Error, TEXT("[%s::%s] " Format), *GetClassName(Object), *FString(__FUNCTION__), ##__VA_ARGS__)

