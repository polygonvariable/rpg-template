#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

template <typename T>
FString GetClassName(const T* Object)
{
    return Object ? Object->GetClass()->GetName() : TEXT("UnknownClass");
}

#define TEXT_INVALID \
    TEXT("INVALID")

#define GET_SUBSYSTEM_FROM_WORLD(SubsystemClass, SubsystemReference) \
    UWorld* World = GetWorld(); \
    if (!World) { \
        UE_LOG(LogTemp, Error, TEXT("[%s] Invalid world"), *FString(__FUNCTION__)); \
        return; \
    } \
    UGameInstance* GameInstance = World->GetGameInstance(); \
    if (!GameInstance) { \
        UE_LOG(LogTemp, Error, TEXT("[%s] Invalid game instance"), *FString(__FUNCTION__)); \
        return; \
    } \
    SubsystemReference = GameInstance->GetSubsystem<SubsystemClass>(); \
    if (!SubsystemReference) { \
        UE_LOG(LogTemp, Error, TEXT("[%s] Invalid subsystem"), *FString(__FUNCTION__)); \
        return; \
    }

#define GET_SUBSYSTEM_FROM_GAMEINSTANCE(SubsystemClass, SubsystemReference) \
    UGameInstance* GameInstance = GetGameInstance(); \
    if (!GameInstance) { \
        UE_LOG(LogTemp, Error, TEXT("[%s] Invalid game instance"), *FString(__FUNCTION__)); \
        return; \
    } \
    SubsystemReference = GameInstance->GetSubsystem<SubsystemClass>(); \
    if (!SubsystemReference) { \
        UE_LOG(LogTemp, Error, TEXT("[%s] Invalid subsystem"), *FString(__FUNCTION__)); \
        return; \
    }

#define GET_SUBSYSTEM(GameInstance, SubsystemClass, SubsystemReference) \
    if (!GameInstance) { \
        UE_LOG(LogTemp, Error, TEXT("[%s] Invalid game instance"), *FString(__FUNCTION__)); \
        return; \
    } \
    SubsystemReference = GameInstance->GetSubsystem<SubsystemClass>(); \
    if (!SubsystemReference) { \
        UE_LOG(LogTemp, Error, TEXT("[%s] Invalid subsystem"), *FString(__FUNCTION__)); \
        return; \
    }


#define LOG_INFO(Category, Object, Format, ...) \
    UE_LOG(Category, Warning, TEXT("[%s::%s] " Format), *GetClassName(Object), *FString(__FUNCTION__), ##__VA_ARGS__)

#define LOG_WARNING(Category, Object, Format, ...) \
    UE_LOG(Category, Warning, TEXT("[%s::%s] " Format), *GetClassName(Object), *FString(__FUNCTION__), ##__VA_ARGS__)

#define LOG_ERROR(Category, Object, Format, ...) \
    UE_LOG(Category, Error, TEXT("[%s::%s] " Format), *GetClassName(Object), *FString(__FUNCTION__), ##__VA_ARGS__)