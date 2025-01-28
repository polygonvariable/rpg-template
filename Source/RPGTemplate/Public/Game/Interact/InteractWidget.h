#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/HUD.h"
#include "InteractComponent.h"
#include "InteractStructs.h"
#include "InteractWidget.generated.h"


UCLASS(DisplayName = "Interact Widget")
class RPGTEMPLATE_API UInteractWidget : public UUserWidget
{

	GENERATED_BODY()
	
public:

	UPROPERTY(Interp, EditAnywhere, Category = "Interact Widget|Item")
	TSet<TObjectPtr<AActor>> InteractActorsSet;


protected:

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Interact Widget|Lifecycle")
	void InitializeStage();
	virtual void InitializeStage_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Interact Widget|Lifecycle")
	void EndStage();
	virtual void EndStage_Implementation();


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Interact Widget|Binding")
	void BindToInteractComponent(bool bIsUnbind);
	virtual void BindToInteractComponent_Implementation(bool bIsUnbind);

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

};
