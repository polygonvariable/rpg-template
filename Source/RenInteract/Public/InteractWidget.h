// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"

// Project Headers
#include "InteractItem.h"

// Generated Headers
#include "InteractWidget.generated.h"

// Forward Declarations
class AInteractActor;


/**
 *
 */
UCLASS(Abstract, DisplayName = "Interact Widget")
class RENINTERACT_API UInteractWidget : public UUserWidget
{

	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, Category = "Interact Widget|Item")
	TSet<TObjectPtr<AActor>> InteractActors;

protected:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Interact Widget|Lifecycle")
	void RegisterInteract();
	virtual void RegisterInteract_Implementation();


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Interact Widget|Lifecycle")
	void UnregisterInteract();
	virtual void UnregisterInteract_Implementation();


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Interact Widget|Binding")
	void HandleComponentBinding(bool bIsUnbind);
	virtual void HandleComponentBinding_Implementation(bool bIsUnbind);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Interact Widget|Item")
	void AddItem(AActor* Actor);
	virtual void AddItem_Implementation(AActor* Actor);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Interact Widget|Item")
	void RemoveItem(AActor* Actor);
	virtual void RemoveItem_Implementation(AActor* Actor);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Interact Widget|Handler")
	void OnItemAdded(AActor* Actor);
	virtual void OnItemAdded_Implementation(AActor* Actor);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Interact Widget|Handler")
	void OnItemRemoved(AActor* Actor);
	virtual void OnItemRemoved_Implementation(AActor* Actor);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Interact Widget|Handler")
	void OnInteractStarted(AActor* Actor);
	virtual void OnInteractStarted_Implementation(AActor* Actor);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Interact Widget|Handler")
	void OnInteractEnded(AActor* Actor);
	virtual void OnInteractEnded_Implementation(AActor* Actor);

protected:

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

};


UCLASS(Abstract, DisplayName = "Interact Entry Widget")
class RENINTERACT_API UInteractEntryWidget : public UUserWidget, public IUserObjectListEntry
{

	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, Category = "Interact Entry Widget|Item")
	FInteractItem InteractItem;


	UPROPERTY(BlueprintReadWrite, Category = "Interact Entry Widget|Item")
	AInteractActor* InteractActor;


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Interact Entry Widget|Action")
	bool InitializeItem(UObject* Object);
	virtual bool InitializeItem_Implementation(UObject* Object);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Interact Entry Widget|Action")
	void Interact();
	virtual void Interact_Implementation();


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Interact Entry Widget|Handler")
	void OnItemUpdated(FInteractItem Item);
	virtual void OnItemUpdated_Implementation(FInteractItem Item);

protected:

	virtual void NativeDestruct() override;

};

