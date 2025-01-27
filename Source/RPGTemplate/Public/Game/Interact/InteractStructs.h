#pragma once

#include "CoreMinimal.h"
#include "InstancedStruct.h"
#include "InteractStructs.generated.h"

USTRUCT(BlueprintType, DisplayName = "Interact Item")
struct FInteractItem
{

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGuid UUID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* Target;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FInstancedStruct CustomData;

	friend inline bool operator == (const FInteractItem& A, const FInteractItem& B)
	{
		return A.UUID == B.UUID;
	}
	friend inline uint32 GetTypeHash(const FInteractItem& Item)
	{
		return GetTypeHash(Item.UUID);
	}

};