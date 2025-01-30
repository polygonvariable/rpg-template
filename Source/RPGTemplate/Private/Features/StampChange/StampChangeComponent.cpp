#include "Features/StampChange/StampChangeComponent.h"

#include "Internal/InternalMacro.h"
#include "Features/Subsystem/StorageSubsystem.h"


void UStampChangeComponent::BeginStage_Implementation(FInstancedStruct Parameters)
{
	UStorageSubsystem* StorageSubsystem = nullptr;
	GET_SUBSYSTEM_FROM_WORLD(UStorageSubsystem, StorageSubsystem);

	if (!StorageSubsystem)
	{
		LOG_ERROR(LogTemp, this, "Failed to get StorageSubsystem");
	}

	bool bIsValid = false;
	Storage = StorageSubsystem->GetLocalStorage(bIsValid);
}

bool UStampChangeComponent::ValidateStage_Implementation()
{
	return IsValid(Storage);
}

void UStampChangeComponent::ActivateStage_Implementation()
{
	OnStampChangeStatus.Broadcast((HasChanged()) ? EStampChangeStatus::Changed : EStampChangeStatus::Unchanged);
}

void UStampChangeComponent::AddChange_Implementation(bool bForce)
{
	if (Storage)
	{
		if (HasChanged() && !bForce)
		{
			return;
		}
		Storage->StampChanges.Add(UUID, FDateTime::Now());
		LOG_INFO(LogTemp, this, "Added changes");
	}
}

void UStampChangeComponent::RemoveChange_Implementation()
{
	if (Storage)
	{
		Storage->StampChanges.Remove(UUID);
		LOG_INFO(LogTemp, this, "Removed changes");
	}
}

bool UStampChangeComponent::HasChanged_Implementation()
{
	if (Storage)
	{
		return Storage->StampChanges.Contains(UUID);
	}
	return false;
}

bool UStampChangeComponent::GetChangedDate_Implementation(FDateTime& ChangedDate)
{
	if (!Storage)
	{
		return false;
	}
	if(Storage->StampChanges.Contains(UUID))
	{
		ChangedDate = Storage->StampChanges.FindChecked(UUID);
		return true;
	}
	return false;
}
