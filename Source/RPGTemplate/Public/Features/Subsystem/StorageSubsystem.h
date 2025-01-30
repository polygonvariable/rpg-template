#pragma once

#include "CoreMinimal.h"

#include "Classes/EGameInstanceSubsystem.h"
#include "Classes/ESaveGame.h"
#include "StorageSubsystem.generated.h"

class UESaveGame;

UCLASS(DisplayName = "Storage Subsystem")
class RPGTEMPLATE_API UStorageSubsystem : public UEGameInstanceSubsystem
{

	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadOnly, Category = "Storage Subsystem|Runtime")
	TObjectPtr<UESaveGame> Storage;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Storage Subsystem")
	void ReadStorage(FName Slot = "Default");
	virtual void ReadStorage_Implementation(FName Slot = "Default");

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Storage Subsystem")
	void UpdateStorage(FName Slot = "Default");
	virtual void UpdateStorage_Implementation(FName Slot = "Default");

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintPure), Category = "Storage Subsystem")
	bool DoesStorageExist(FName Slot = "Default");
	virtual bool DoesStorageExist_Implementation(FName Slot = "Default");

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Storage Subsystem")
	UESaveGame* GetLocalStorage(bool& bIsValid);
	virtual UESaveGame* GetLocalStorage_Implementation(bool& bIsValid);

public:

	virtual void OnInitialized_Implementation() override;

};
