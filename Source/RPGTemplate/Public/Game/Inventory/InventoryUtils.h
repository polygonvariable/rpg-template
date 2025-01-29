#pragma once

#include "CoreMinimal.h"
#include "InstancedStruct.h"
#include "InventoryUtils.generated.h"

class UInventoryAsset;

UENUM(BlueprintType, DisplayName = "Inventory Type")
enum EInventoryType
{
    Food UMETA(DisplayName = "Food"),
    Material UMETA(DisplayName = "Material"),
    Skill UMETA(DisplayName = "Skill"),
    Weapon UMETA(DisplayName = "Weapon"),
    Enhance UMETA(DisplayName = "Enhance"),
    Photo UMETA(DisplayName = "Photo"),
};

UENUM(BlueprintType, DisplayName = "Inventory Rarity")
enum EInventoryRarity
{
    Common UMETA(DisplayName = "Common"),
	Rare UMETA(DisplayName = "Rare"),
	Epic UMETA(DisplayName = "Epic"),
	Legendary UMETA(DisplayName = "Legendary"),
};


USTRUCT(BlueprintType, DisplayName = "Interact Item")
struct FInventoryItem
{

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Quantity = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Type = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Rank = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Xp = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FInstancedStruct CustomData;

	friend inline bool operator == (const FInventoryItem& A, const FInventoryItem& B)
	{
		return A.Id == B.Id && A.Type == B.Type;
	}
	friend inline uint32 GetTypeHash(const FInventoryItem& Item)
	{
		return HashCombine(GetTypeHash(Item.Id.ToString()), GetTypeHash(Item.Type));
	}

};

USTRUCT(BlueprintType, DisplayName = "Interact Item Mapping")
struct FInventoryItemTable : public FTableRowBase
{

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInventoryAsset* InventoryAsset = nullptr;

	friend inline bool operator == (const FInventoryItemTable& A, const FInventoryItemTable& B)
	{
		return A.Id == B.Id;
	}
	friend inline uint32 GetTypeHash(const FInventoryItemTable& Item)
	{
		return GetTypeHash(Item.Id.ToString());
	}

};