// Fill out your copyright notice in the Description page of Project Settings.


#include "LifeCycle/LifeCycleLibrary.h"

#include "RenGlobal/Public/Macro/LogMacro.h"
#include "LifeCycle/LifeCycleInterface.h"


#define EXECUTE_INTERFACE(Target, Interface, Function, ...) \
    if (IsValid(Target) && Target->Implements<Interface>()) \
    { \
        Function(Target, __VA_ARGS__); \
    }


void ULifeCycleLibrary::StartLifecycle(UObject* Target, FInstancedStruct Parameters, const bool bSkipLoad, const bool bSkipValidate)
{
    if (ILifeCycleInterface* Interface = Cast<ILifeCycleInterface>(Target))
    {
        Interface->StartLifecycle(Target, Parameters, bSkipLoad, bSkipValidate);
    }
}

void ULifeCycleLibrary::StartLifecycleWithLoader(UObject* Target, FInstancedStruct Parameters, const bool bSkipValidate)
{
    StartLifecycle(Target, Parameters, false, bSkipValidate);
}

void ULifeCycleLibrary::StartLifecycleWithValidation(UObject* Target, FInstancedStruct Parameters, const bool bSkipLoad)
{
    StartLifecycle(Target, Parameters, bSkipLoad, true);
}

void ULifeCycleLibrary::Loaded(UObject* Target)
{
    if (ILifeCycleInterface* Interface = Cast<ILifeCycleInterface>(Target))
    {
        Interface->OnLoaded(Target);
    }
}

