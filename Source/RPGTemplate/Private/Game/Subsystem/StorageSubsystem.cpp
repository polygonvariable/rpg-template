#include "Game/Subsystem/StorageSubsystem.h"

#include "Kismet/GameplayStatics.h"

#include "Internal/InternalMacro.h"


void UStorageSubsystem::ReadStorage_Implementation(TSubclassOf<UESaveGame> StorageClass, FName Slot)
{
	if (!Storage || Storage->GetClass() != StorageClass) {
		if (DoesStorageExist(Slot)) {

			Storage = Cast<UESaveGame>(UGameplayStatics::LoadGameFromSlot(Slot.ToString(), 0));
			LOG_INFO(LogTemp, this, "Storage loaded from slot");

		}
		else {

			USaveGame* NewSaveGame = UGameplayStatics::CreateSaveGameObject(StorageClass);
			if (!NewSaveGame) {
				LOG_ERROR(LogTemp, this, "Failed to create save game object");
				return;
			}

			UGameplayStatics::SaveGameToSlot(NewSaveGame, Slot.ToString(), 0);
			Storage = Cast<UESaveGame>(NewSaveGame);

		}
	}
	else {
		LOG_INFO(LogTemp, this, "Storage already exists or invalid class");
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