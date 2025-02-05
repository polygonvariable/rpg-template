// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "StampedEvent/StampedEventComponent.h"

// Project Headers
#include "RenShared/Public/Macro/GameInstanceMacro.h"
#include "RenShared/Public/Macro/LogMacro.h"
#include "RenStorage/Public/Storage.h"
#include "RenStorage/Public/StorageSubsystem.h"


void UStampedEventComponent::BeginStage_Implementation(const FInstancedStruct Parameters)
{
	UStorageSubsystem* StorageSubsystem;
    GET_SUBSYSTEM_FROM_WORLD(UStorageSubsystem, StorageSubsystem);

	bool bIsValid = false;
	Storage = StorageSubsystem->GetLocalStorage(bIsValid);
}

bool UStampedEventComponent::ValidateStage_Implementation()
{
	return IsValid(Storage);
}

void UStampedEventComponent::ActivateStage_Implementation()
{
	OnStampedEventStatus.Broadcast((HasChanged()) ? EStampedEventStatus::Changed : EStampedEventStatus::Unchanged);
}

void UStampedEventComponent::AddChange_Implementation(const bool bForce)
{
	if (IsValid(Storage)) {
		if (HasChanged() && !bForce) {
			return;
		}
		Storage->StampedEvents.Add(UUID, FDateTime::Now());
		LOG_INFO(this, LogTemp, "Stamped event added");
	}
}

void UStampedEventComponent::RemoveChange_Implementation()
{
	if (IsValid(Storage)) {
		Storage->StampedEvents.Remove(UUID);
		LOG_INFO(this, LogTemp, "Stamped event removed");
	}
}

bool UStampedEventComponent::HasChanged_Implementation()
{
	if (!IsValid(Storage)) {
	    return false;
	}
	return Storage->StampedEvents.Contains(UUID);
}

bool UStampedEventComponent::GetEventDate_Implementation(FDateTime& EventDate)
{
	if (!IsValid(Storage)) {
		return false;
	}
	if(Storage->StampedEvents.Contains(UUID)) {
		EventDate = Storage->StampedEvents.FindChecked(UUID);
		return true;
	}
	return false;
}

