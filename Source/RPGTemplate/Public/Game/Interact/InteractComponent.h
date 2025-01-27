#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractStructs.h"
#include "InteractComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), DisplayName = "Interact Component")
class RPGTEMPLATE_API UInteractComponent : public UActorComponent
{


	GENERATED_BODY()


public:	


	UInteractComponent();


	UPROPERTY(EditAnywhere, Category = "Interact Component|Item")
	TSet<FInteractItem> Items;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Interact Component|Item")
	void AddItem(FInteractItem Item);
	virtual void AddItem_Implementation(FInteractItem Item);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Interact Component|Item")
	void RemoveItem(FInteractItem Item);
	virtual void RemoveItem_Implementation(FInteractItem Item);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintPure), Category = "Interact Component|Item")
	bool ItemExists(FInteractItem Item);
	virtual bool ItemExists_Implementation(FInteractItem Item);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemAdded, FInteractItem, Item);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Interact Component|Event Dispatcher")
	FOnItemAdded OnItemAdded;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemRemoved, FInteractItem, Item);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Interact Component|Event Dispatcher")
	FOnItemRemoved OnItemRemoved;

protected:


	virtual void BeginPlay() override;


public:


	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
