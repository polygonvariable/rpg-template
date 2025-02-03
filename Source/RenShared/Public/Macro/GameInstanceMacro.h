// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"


#define GET_SUBSYSTEM_FROM_WORLD(SubsystemClass, SubsystemReference) \
    UWorld* World = GetWorld(); \
    if (!IsValid(World)) { \
        UE_LOG(LogTemp, Error, TEXT("[%s] Invalid world"), *FString(__FUNCTION__)); \
        return; \
    } \
    UGameInstance* GameInstance = World->GetGameInstance(); \
    GET_SUBSYSTEM(GameInstance, SubsystemClass, SubsystemReference)


#define GET_SUBSYSTEM_FROM_GAMEINSTANCE(SubsystemClass, SubsystemReference) \
    UGameInstance* GameInstance = GetGameInstance(); \
    GET_SUBSYSTEM(GameInstance, SubsystemClass, SubsystemReference)


#define GET_SUBSYSTEM(GameInstance, SubsystemClass, SubsystemReference) \
    if (!IsValid(GameInstance)) { \
        UE_LOG(LogTemp, Error, TEXT("[%s] Invalid game instance"), *FString(__FUNCTION__)); \
        return; \
    } \
    SubsystemReference = GameInstance->GetSubsystem<SubsystemClass>(); \
    if (!IsValid(SubsystemReference)) { \
        UE_LOG(LogTemp, Error, TEXT("[%s] Invalid subsystem"), *FString(__FUNCTION__)); \
        return; \
    }

