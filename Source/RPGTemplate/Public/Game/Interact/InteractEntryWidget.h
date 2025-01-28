#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "InteractActor.h"
#include "InteractStructs.h"
#include "InteractEntryWidget.generated.h"


UCLASS(Abstract, DisplayName = "Interact Entry Widget")
class RPGTEMPLATE_API UInteractEntryWidget : public UUserWidget, public IUserObjectListEntry
{

	GENERATED_BODY()
	
public:

	UPROPERTY(Interp, EditAnywhere, Category = "Interact Entry Widget|Item")
	FInteractItem InteractItem;

	UPROPERTY(Interp, EditAnywhere, Category = "Interact Entry Widget|Item")
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
	

	virtual void NativeDestruct() override;

};
