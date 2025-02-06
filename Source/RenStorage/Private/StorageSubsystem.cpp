// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "StorageSubsystem.h"

// Engine Headers
#include "Kismet/GameplayStatics.h"

// Project Headers
#include "Storage.h"
#include "RenShared/Public/Macro/LogMacro.h"
#include "RenCore/Public/Developer/GameMetadataSettings.h"


void UStorageSubsystem::ReadStorage_Implementation(const FName Slot)
{
	const UGameMetadataSettings* Settings = GetDefault<UGameMetadataSettings>();

	/*const TSubclassOf<USaveGame> StorageClass = Settings->StorageClass;
	const TSubclassOf<UStorage> StorageClasss = Settings->StorageClasses.TryLoadClass<UStorage>();
	if (Storage || !StorageClass || !StorageClass->IsChildOf(UStorage::StaticClass()))
	{
		LOG_ERROR(this, LogTemp, "Storage is already set or StorageClass is null or not a child of ESaveGame");
		return;
	}*/

	if (DoesStorageExist(Slot))
	{
		Storage = Cast<UStorage>(UGameplayStatics::LoadGameFromSlot(Slot.ToString(), 0));
		LOG_INFO(this, LogTemp, "Storage loaded from slot");
	}
	else
	{
		USaveGame* NewSaveGame = UGameplayStatics::CreateSaveGameObject(UStorage::StaticClass());
		if (!IsValid(NewSaveGame))
		{
			LOG_ERROR(this, LogTemp, "Failed to create save game object");
			return;
		}

		UGameplayStatics::SaveGameToSlot(NewSaveGame, Slot.ToString(), 0);
		Storage = Cast<UStorage>(NewSaveGame);

		LOG_INFO(this, LogTemp, "Storage created and saved to slot");
	}
}

void UStorageSubsystem::UpdateStorage_Implementation(const FName Slot)
{
	if (!IsValid(Storage))
	{
		LOG_ERROR(this, LogTemp, "Storage is null");
		return;
	}
	UGameplayStatics::SaveGameToSlot(Storage, Slot.ToString(), 0);
}

bool UStorageSubsystem::DoesStorageExist_Implementation(const FName Slot)
{
	return UGameplayStatics::DoesSaveGameExist(Slot.ToString(), 0);
}

UStorage* UStorageSubsystem::GetLocalStorage_Implementation(bool& bIsValid)
{
	bIsValid = IsValid(Storage);
	return Storage;
}


void UStorageSubsystem::OnInitialized_Implementation()
{
	Super::OnInitialized_Implementation();
	ReadStorage();
}

void UStorageSubsystem::OnDeinitialized_Implementation()
{
	UpdateStorage();
	Super::OnDeinitialized_Implementation();
}
