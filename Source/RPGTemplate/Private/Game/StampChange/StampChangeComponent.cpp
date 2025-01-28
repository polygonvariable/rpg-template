#include "Game/StampChange/StampChangeComponent.h"

void UStampChangeComponent::BeginStage_Implementation(FInstancedStruct Parameters)
{
	UGameInstance* GameInstance = GetWorld()->GetGameInstance();
	if (!GameInstance) {
		return;
	}

	UStorageSubsystem* StorageSubsystem = CastChecked<UStorageSubsystem>(GameInstance->GetSubsystem<UStorageSubsystem>());
	if (StorageSubsystem) {

		bool bIsValid = false;
		Storage = StorageSubsystem->GetLocalStorage(bIsValid);

	}
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
	if (Storage) {
		if (HasChanged() && !bForce) {
			return;
		}
		Storage->StampChanges.Add(UUID, FDateTime::Now());
	}
}

void UStampChangeComponent::RemoveChange_Implementation()
{
	if (Storage) {
		Storage->StampChanges.Remove(UUID);
	}
}

bool UStampChangeComponent::HasChanged_Implementation()
{
	if (Storage) {
		return Storage->StampChanges.Contains(UUID);
	}
	return false;
}

bool UStampChangeComponent::GetChangedDate_Implementation(FDateTime& ChangedDate)
{
	if (!Storage) {
		return false;
	}
	if(Storage->StampChanges.Contains(UUID)) {
		ChangedDate = Storage->StampChanges.FindChecked(UUID);
		return true;
	}
	return false;
}
