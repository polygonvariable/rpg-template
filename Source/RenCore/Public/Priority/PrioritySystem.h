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

	UFUNCTION()
	virtual void AddItem(FInstancedStruct Item, int Priority);

	UFUNCTION()
	virtual void RemoveItem(int Priority);

	UFUNCTION()
	int GetHighestPriority() const;

protected:

	// TODO
	// Will be removed
	UPROPERTY(BlueprintReadOnly)
	FInstancedStruct ActiveItem;

	UPROPERTY(BlueprintReadOnly)
	TMap<int, FInstancedStruct> Items;

	UFUNCTION()
	virtual void HandleItemAdded(const FInstancedStruct& Item);

	UFUNCTION()
	virtual void HandleItemRemoved(const FInstancedStruct& Item);

	UFUNCTION()
	virtual void HandleItemChanged(const FInstancedStruct& Item);

public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemAdded, const FInstancedStruct&, Item);
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnItemAdded OnItemAdded;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemRemoved, const FInstancedStruct&, Item);
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnItemRemoved OnItemRemoved;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemChanged, const FInstancedStruct&, Item);
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnItemChanged OnItemChanged;

};

