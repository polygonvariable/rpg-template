#include "Subsystem/StorageSubsystem.h"

#include "Kismet/GameplayStatics.h"

#include "Internal/InternalMacro.h"
#include "Developer/GameMetadataSettings.h"


void UStorageSubsystem::ReadStorage_Implementation(FName Slot)
{
	const UGameMetadataSettings* Settings = GetDefault<UGameMetadataSettings>();
	const TSubclassOf<USaveGame> StorageClass = Settings->StorageClass;

	if (Storage || !StorageClass || !StorageClass->IsChildOf(UESaveGame::StaticClass()))
	{
		LOG_ERROR(LogTemp, this, "Storage is already set or StorageClass is null or not a child of ESaveGame");
		return;
	}

	if (DoesStorageExist(Slot))
	{
		Storage = Cast<UESaveGame>(UGameplayStatics::LoadGameFromSlot(Slot.ToString(), 0));
		LOG_INFO(LogTemp, this, "Storage loaded from slot");
	}
	else
	{
		USaveGame* NewSaveGame = UGameplayStatics::CreateSaveGameObject(StorageClass);
		if (!NewSaveGame)
		{
			LOG_ERROR(LogTemp, this, "Failed to create save game object");
			return;
		}

		UGameplayStatics::SaveGameToSlot(NewSaveGame, Slot.ToString(), 0);
		Storage = Cast<UESaveGame>(NewSaveGame);
	}
}

void UStorageSubsystem::UpdateStorage_Implementation(FName Slot)
{
	if (!Storage)
	{
		LOG_ERROR(LogTemp, this, "Storage is null");
		return;
	}
	UGameplayStatics::SaveGameToSlot(Storage, Slot.ToString(), 0);
}

bool UStorageSubsystem::DoesStorageExist_Implementation(FName Slot)
{
	return UGameplayStatics::DoesSaveGameExist(Slot.ToString(), 0);
}

UESaveGame* UStorageSubsystem::GetLocalStorage_Implementation(bool& bIsValid)
{
	if (Storage)
	{
		bIsValid = true;
		return Storage;
	}
	bIsValid = false;
	return nullptr;
}

void UStorageSubsystem::OnInitialized_Implementation()
{
	Super::OnInitialized_Implementation();
	ReadStorage();
}