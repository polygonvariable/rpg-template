// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"
#include "InstancedStruct.h"

// Generated Headers
#include "PrioritySystem.generated.h"


/**
 *
 */
UCLASS()
class RENCORE_API UPrioritySystem : public UObject
{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FInstancedStruct ActiveItem;


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Action")
	void AddItem(FInstancedStruct Item, const int Priority);
	virtual void AddItem_Implementation(FInstancedStruct Item, const int Priority);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Action")
	void RemoveItem(const int Priority);
	virtual void RemoveItem_Implementation(const int Priority);


	UFUNCTION(BlueprintCallable)
	int GetHighestPriority();


protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<int, FInstancedStruct> Items;


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Handler")
	void OnItemAdded(FInstancedStruct Item);
	virtual void OnItemAdded_Implementation(FInstancedStruct Item);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Handler")
	void OnItemRemoved(FInstancedStruct Item);
	virtual void OnItemRemoved_Implementation(FInstancedStruct Item);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Handler")
	void OnActiveItemChanged();
	virtual void OnActiveItemChanged_Implementation();

};

