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

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<int, FInstancedStruct> Items;

	int GetHighestPriority();

public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemAdded, FInstancedStruct, Item);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Event Dispatcher")
	FOnItemAdded OnItemAdded;


	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemRemoved, FInstancedStruct, Item);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Event Dispatcher")
	FOnItemRemoved OnItemRemoved;


	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemChanged, FInstancedStruct, Item);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Event Dispatcher")
	FOnItemChanged OnItemChanged;

};

