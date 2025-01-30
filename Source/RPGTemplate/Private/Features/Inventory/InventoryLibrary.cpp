#include "Features/Inventory/InventoryLibrary.h"

TSet<FName> UInventoryLibrary::GetNamedInventoryTypes()
{
	TSet<FName> NamedTypes;
	TArray<FString> Types = UInventoryLibrary::GetInventoryTypes();

	for (FString Type : Types)
	{
		NamedTypes.Add(FName(Type));
	}

	return NamedTypes;
}

TSet<FName> UInventoryLibrary::GetNamedInventoryRarities()
{
	TSet<FName> NamedRarities;
	TArray<FString> Rarities = UInventoryLibrary::GetInventoryRarities();

	for (FString Rarity : Rarities)
	{
		NamedRarities.Add(FName(Rarity));
	}

	return NamedRarities;
}