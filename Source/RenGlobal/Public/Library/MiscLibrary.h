// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"


#include "MiscLibrary.generated.h"



template <typename TSubsystemType, typename TContextType>
bool GetSubsystemReference(TContextType* Context, TObjectPtr<TSubsystemType>& OutSubsystem)
{
	if (IsValid(OutSubsystem)) return true;

	OutSubsystem = nullptr;
	if (!IsValid(Context)) return false;

	OutSubsystem = Context->GetSubsystem<TSubsystemType>();
	return IsValid(OutSubsystem);
}

template <typename TSubsystem, typename TContext>
TSubsystem* GetSubsystem(TContext* Context)
{
	if (!IsValid(Context)) return nullptr;
	return Context->GetSubsystem<TSubsystem>();
}


template <typename TSubsystem>
TSubsystem* GetGameInstanceSubsystem(UWorld* WorldContext)
{
	if (!IsValid(WorldContext)) return nullptr;

	UGameInstance* GameInstance = WorldContext->GetGameInstance();
	if (!IsValid(GameInstance)) return nullptr;

	return GameInstance->GetSubsystem<TSubsystem>();
}

UCLASS()
class RENGLOBAL_API UMiscLibrary : public UObject
{

	GENERATED_BODY()

public:

	static bool IsInGameWorld(UWorld* World)
	{
		return World &&
		(
			World->WorldType == EWorldType::Game ||
			World->WorldType == EWorldType::GamePreview ||
			World->WorldType == EWorldType::GameRPC ||
			World->WorldType == EWorldType::PIE
		);
	}

};

