// Fill out your copyright notice in the Description page of Project Settings.


//
#include "EnvironmentSubsystem.h"

// Project Headers
#include "RenCore/Public/Priority/PrioritySystem.h"
#include "RenShared/Public/Macro/GameInstanceMacro.h"
#include "RenShared/Public/Macro/LogMacro.h"


UEnvironmentSubsystem::UEnvironmentSubsystem()
{
	RegionPrioritySystem = NewObject<UPrioritySystem>();
}

void UEnvironmentSubsystem::PostInitialize_Implementation()
{
	Super::PostInitialize_Implementation();
}

