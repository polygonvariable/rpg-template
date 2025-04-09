// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "LifeCycle/LifeCycleInterface.h"

// Project Headers
#include "RenGlobal/Public/Macro/LogMacro.h"


void ILifeCycleInterface::StartLifecycle(UObject* Target, FInstancedStruct Parameters, const bool bSkipLoad, const bool bSkipValidate)
{
	if (!IsValid(Target))
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Target"));
		return;
	}

	if (bStarted)
	{
		UE_LOG(LogTemp, Warning, TEXT("Lifecycle already started"));
		return;
	}

	Execute_BeginStage(Target, Parameters);
	bStarted = true;

	if (!bSkipLoad)
	{
		Execute_LoadStage(Target);
	}
	else
	{
		if (!bSkipValidate && Execute_ValidateStage(Target))
		{
			Execute_ActivateStage(Target);
		}
		else if (bSkipValidate)
		{
			Execute_ActivateStage(Target);
		}
	}
}

void ILifeCycleInterface::OnLoaded(UObject* Target)
{
	if (!bStarted)
	{
		UE_LOG(LogTemp, Warning, TEXT("Lifecycle not started"));
		return;
	}
	if (!Target)
	{
		if (Execute_ValidateStage(Target))
		{
			Execute_ActivateStage(Target);
		}
	}
}
