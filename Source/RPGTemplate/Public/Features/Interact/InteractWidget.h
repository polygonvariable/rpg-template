#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "InteractStructs.h"

#include "InteractWidget.generated.h"

class AInteractActor;


UCLASS(Abstract, DisplayName = "Interact Widget")
class RPGTEMPLATE_API UInteractWidget : public UUserWidget
{

	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite, Category = "Interact Widget|Item")
	TSet<TObjectPtr<AActor>> InteractActorsSet;

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
	void AddItem(AActor* Item);
	virtual void AddItem_Implementation(AActor* Item);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Interact Widget|Item")
	void RemoveItem(AActor* Item);
	virtual void RemoveItem_Implementation(AActor* Item);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Interact Widget|Handler")
	void OnItemAdded(AActor* Item);
	virtual void OnItemAdded_Implementation(AActor* Item);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Interact Widget|Handler")
	void OnItemRemoved(AActor* Item);
	virtual void OnItemRemoved_Implementation(AActor* Item);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Interact Widget|Handler")
	void OnInteractStarted(AActor* Item);
	virtual void OnInteractStarted_Implementation(AActor* Item);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Interact Widget|Handler")
	void OnInteractEnded(AActor* Item);
	virtual void OnInteractEnded_Implementation(AActor* Item);

protected:

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

};


UCLASS(Abstract, DisplayName = "Interact Entry Widget")
class RPGTEMPLATE_API UInteractEntryWidget : public UUserWidget, public IUserObjectListEntry
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
