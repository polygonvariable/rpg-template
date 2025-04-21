// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "StorageSubsystem.h"

// Engine Headers
#include "Kismet/GameplayStatics.h"

// Project Headers
#include "Storage.h"
#include "RenGlobal/Public/Macro/LogMacro.h"
#include "RenCore/Public/Developer/GameMetadataSettings.h"


void UStorageSubsystem::ReadStorage_Implementation(const FName SlotId)
{
	const UGameMetadataSettings* Settings = GetDefault<UGameMetadataSettings>();

	/*const TSubclassOf<USaveGame> StorageClass = Settings->StorageClass;
	const TSubclassOf<UStorage> StorageClasss = Settings->StorageClasses.TryLoadClass<UStorage>();
	if (Storage || !StorageClass || !StorageClass->IsChildOf(UStorage::StaticClass()))
	{
		LOG_ERROR(LogTemp, "Storage is already set or StorageClass is null or not a child of ESaveGame");
		return;
	}*/

	if (DoesStorageExist(SlotId))
	{
		Storage = Cast<UStorage>(UGameplayStatics::LoadGameFromSlot(SlotId.ToString(), 0));
		LOG_INFO(LogTemp, "Storage loaded from slot");
	}
	else
	{
		USaveGame* NewSaveGame = UGameplayStatics::CreateSaveGameObject(UStorage::StaticClass());
		if (!IsValid(NewSaveGame))
		{
			LOG_ERROR(LogTemp, "Failed to create save game object");
			return;
		}

		UGameplayStatics::SaveGameToSlot(NewSaveGame, SlotId.ToString(), 0);
		Storage = Cast<UStorage>(NewSaveGame);

		LOG_INFO(LogTemp, "Storage created and saved to slot");
	}
}

void UStorageSubsystem::UpdateStorage_Implementation(const FName SlotId)
{
	if (!IsValid(Storage))
	{
		LOG_ERROR(LogTemp, "Storage is null");
		return;
	}
	UGameplayStatics::SaveGameToSlot(Storage, SlotId.ToString(), 0);
}

bool UStorageSubsystem::DoesStorageExist_Implementation(const FName SlotId)
{
	return UGameplayStatics::DoesSaveGameExist(SlotId.ToString(), 0);
}

UStorage* UStorageSubsystem::GetLocalStorage_Implementation()
{
	return IsValid(Storage) ? Storage : nullptr;
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
