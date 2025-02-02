// Fill out your copyright notice in the Description page of Project Settings.


#include "LifeCycle/LifeCycleLibrary.h"

#include "LifeCycle/LifeCycleInterface.h"


void ULifeCycleLibrary::StartLifecycle(UObject* Target, const FInstancedStruct& Parameters, const bool bSkipLoad, const bool bSkipValidate)
{
    if (ILifeCycleInterface* Interface = Cast<ILifeCycleInterface>(Target))
    {
        Interface->StartLifecycle(Target, Parameters, bSkipLoad, bSkipValidate);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Target does not implement ILifeCycleInterface"));
    }
}

void ULifeCycleLibrary::StartLifecycleWithLoader(UObject* Target, const FInstancedStruct& Parameters, const bool bSkipValidate)
{
    StartLifecycle(Target, Parameters, false, bSkipValidate);
}

void ULifeCycleLibrary::StartLifecycleWithValidation(UObject* Target, const FInstancedStruct& Parameters, const bool bSkipLoad)
{
    StartLifecycle(Target, Parameters, bSkipLoad, true);
}

void ULifeCycleLibrary::Loaded(UObject* Target)
{
    if (ILifeCycleInterface* Interface = Cast<ILifeCycleInterface>(Target))
    {
        Interface->OnLoaded(Target);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Target does not implement ILifeCycleInterface"));
    }
}

