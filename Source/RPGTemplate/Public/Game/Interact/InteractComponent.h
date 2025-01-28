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

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Interact Component|Item")
	void AddItem(AActor* Item);
	virtual void AddItem_Implementation(AActor* Item);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Interact Component|Item")
	void RemoveItem(AActor* Item);
	virtual void RemoveItem_Implementation(AActor* Item);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractStarted, AActor*, Item);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Interact Component|Event Dispatcher")
	FOnInteractStarted OnInteractStarted;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractEnded, AActor*, Item);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Interact Component|Event Dispatcher")
	FOnInteractEnded OnInteractEnded;

protected:


	virtual void BeginPlay() override;


public:


	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
