#include "Game/Subsystem/StorageSubsystem.h"

UStorageSubsystem::UStorageSubsystem()
{
	bAllowCreation = true;
}

void UStorageSubsystem::ReadStorage_Implementation(TSubclassOf<UESaveGame> StorageClass, FName Slot)
{
	if (!Storage || Storage->GetClass() != StorageClass) {
		if (DoesStorageExist(Slot)) {

			Storage = Cast<UESaveGame>(UGameplayStatics::LoadGameFromSlot(Slot.ToString(), 0));
			UE_LOG(LogTemp, Warning, TEXT("[%s]: Storage loaded from slot"), *this->GetName());

		}
		else {

			USaveGame* NewSaveGame = UGameplayStatics::CreateSaveGameObject(StorageClass);

			if (!NewSaveGame) {
				UE_LOG(LogTemp, Warning, TEXT("[%s]: Failed to create save game object"), *this->GetName());
				return;
			}
			UGameplayStatics::SaveGameToSlot(NewSaveGame, Slot.ToString(), 0);

			Storage = Cast<UESaveGame>(NewSaveGame);

		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("[%s]: Storage already exists or invalid class"), *this->GetName());
	}
}

void UStorageSubsystem::UpdateStorage_Implementation(FName Slot)
{
	if (Storage) {
		UGameplayStatics::SaveGameToSlot(Storage, Slot.ToString(), 0);
	}
}

bool UStorageSubsystem::DoesStorageExist_Implementation(FName Slot)
{
	return UGameplayStatics::DoesSaveGameExist(Slot.ToString(), 0);
}

UESaveGame* UStorageSubsystem::GetLocalStorage_Implementation(bool& bIsValid)
{
	if (Storage) {
		bIsValid = true;
		return Storage;
	}
	bIsValid = false;
	return nullptr;
}

void UStorageSubsystem::OnInitialized_Implementation()
{
	Super::OnInitialized_Implementation();
	ReadStorage(UESaveGame::StaticClass());
}