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

	UFUNCTION(BlueprintCallable)
	int GetHighestPriority() const;

protected:

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

};

