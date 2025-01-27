#pragma once

#include "CoreMinimal.h"
#include "Classes/EActor.h"
#include "InteractStructs.h"
#include "InteractComponent.h"
#include "GameFramework/HUD.h"
#include "InteractActor.generated.h"


UCLASS(DisplayName = "Interact Actor")
class RPGTEMPLATE_API AInteractActor : public AEActor
{


	GENERATED_BODY()
	

public:


	AInteractActor();

	UPROPERTY(Interp, EditAnywhere, Category = "Interact Actor|Item")
	FGuid UUID = FGuid::NewGuid();

	UPROPERTY(Interp, EditAnywhere, Category = "Interact Actor|Item")
	FText Name = FText::FromString("Item");


protected:


	UPROPERTY(Interp, BlueprintReadOnly, Category = "Interact Actor|Generated")
	FInteractItem InteractItem;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected, BlueprintPure), Category = "Interact Actor|Action")
	UInteractComponent* GetInteractComponent() const;
	virtual UInteractComponent* GetInteractComponent_Implementation() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Interact Actor|Action")
	void StartInteract();
	virtual void StartInteract_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Interact Actor|Action")
	void EndInteract();
	virtual void EndInteract_Implementation();


};
