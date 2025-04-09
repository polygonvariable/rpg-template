// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"

// Project Headers
#include "RenCore/Public/Subsystem/RenGameInstanceSubsystem.h"

// Generated Headers
#include "StorageSubsystem.generated.h"

// Forward Declarations
class UStorage;


/**
 * 
 */
UCLASS(DisplayName = "Storage Subsystem")
class RENSTORAGE_API UStorageSubsystem : public URenGameInstanceSubsystem
{

	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, Category = "Runtime")
	TObjectPtr<UStorage> Storage;

	//UPROPERTY(BlueprintReadOnly, Category = "Runtime")
	//TMap<FName, TObjectPtr<UStorage>> Storages;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction))
	void ReadStorage(const FName SlotId = "Default");
	virtual void ReadStorage_Implementation(const FName SlotId = "Default");

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction))
	void UpdateStorage(const FName SlotId = "Default");
	virtual void UpdateStorage_Implementation(const FName SlotId = "Default");

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintPure))
	bool DoesStorageExist(const FName SlotId = "Default");
	virtual bool DoesStorageExist_Implementation(const FName SlotId = "Default");

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction))
	UStorage* GetLocalStorage();
	virtual UStorage* GetLocalStorage_Implementation();

protected:

	virtual void OnInitialized_Implementation() override;
	virtual void OnDeinitialized_Implementation() override;

};
