#pragma once

#include "CoreMinimal.h"
#include "Classes/EActor.h"
#include "InteractStructs.h"
#include "InteractComponent.h"
#include "GameFramework/HUD.h"
#include "InteractActor.generated.h"


UCLASS(Abstract, DisplayName = "Interact Actor")
class RPGTEMPLATE_API AInteractActor : public AEActor
{

	GENERATED_BODY()
	
public:

	UPROPERTY(Interp, EditAnywhere, Category = "Interact Actor|Item")
	FGuid GUID = FGuid::NewGuid();

	UPROPERTY(Interp, EditAnywhere, Category = "Interact Actor|Item")
	FText Name = FText::FromString("Item");

	FInteractItem& GetInteractItem();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Interact Actor|Action")
	void Interact();
	virtual void Interact_Implementation();

protected:

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(Interp, AdvancedDisplay, Category = "Interact Actor|Item")
	FInteractItem InteractItem;


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Interact Actor|Item")
	void BuildItem();
	virtual void BuildItem_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected, BlueprintPure), Category = "Interact Actor|Action")
	UInteractComponent* GetInteractComponent() const;
	virtual UInteractComponent* GetInteractComponent_Implementation() const;


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Interact Actor|Action")
	void StartInteract();
	virtual void StartInteract_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Interact Actor|Action")
	void EndInteract();
	virtual void EndInteract_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Interact Actor|Action")
	void UpdateItem();
	virtual void UpdateItem_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Interact Actor|Handler")
	void OnInteracted();
	virtual void OnInteracted_Implementation();

public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemUpdated, FInteractItem, Item);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Interact Actor|Event Dispatcher")
	FOnItemUpdated OnItemUpdated;

};
