#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/HUD.h"
#include "InteractComponent.h"
#include "InteractStructs.h"
#include "InteractWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPGTEMPLATE_API UInteractWidget : public UUserWidget
{

	GENERATED_BODY()
	
public:

	UPROPERTY(Interp, EditAnywhere, Category = "Interact Widget|Item")
	TMap<FGuid, TObjectPtr<UObject>> InteractItems;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Interact Widget|Binding")
	void BindToInteractComponent();
	virtual void BindToInteractComponent_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Interact Widget|Item")
	UObject* AddItem(FInteractItem Item);
	virtual UObject* AddItem_Implementation(FInteractItem Item);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Interact Widget|Item")
	void RemoveItem(FInteractItem Item);
	virtual void RemoveItem_Implementation(FInteractItem Item);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Interact Widget|Handler")
	void OnItemAdded(FInteractItem Item);
	virtual void OnItemAdded_Implementation(FInteractItem Item);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Interact Widget|Handler")
	void OnItemRemoved(FInteractItem Item);
	virtual void OnItemRemoved_Implementation(FInteractItem Item);

};
