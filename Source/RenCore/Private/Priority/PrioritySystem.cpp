// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Priority/PrioritySystem.h"
#include "RenGlobal/Public/Macro/LogMacro.h"


void UPrioritySystem::AddItem(FInstancedStruct Item, const int Priority)
{
	if (!Item.IsValid() || Priority < 0)
	{
		LOG_ERROR(LogTemp, "Item is not valid or Priority is less than 0");
		return;
	}

	int HighestPriority = GetHighestPriority();

	Items.Add(Priority, Item);
	HandleItemAdded(Item);

	if (Priority > HighestPriority)
	{
		ActiveItem = Item;
		HandleItemChanged(ActiveItem);
	}
	else
	{
		LOG_WARNING(LogTemp, "Priority is less than highest priority, added in queue");
	}
}

void UPrioritySystem::RemoveItem(const int Priority)
{
	FInstancedStruct* Item = Items.Find(Priority);
	if (!Item)
	{
		LOG_WARNING(LogTemp, "Priority not found");
		return;
	}

	int CurrentPriority = GetHighestPriority();
	
	Items.Remove(Priority);
	HandleItemRemoved(*Item);

	if (Priority != CurrentPriority) return;

	int NewPriority = GetHighestPriority();
	if (FInstancedStruct* NewItem = Items.Find(NewPriority))
	{
		ActiveItem = *NewItem;
		if (ActiveItem.IsValid()) HandleItemChanged(ActiveItem);
	}
}

int UPrioritySystem::GetHighestPriority()
{
	if (Items.Num() == 0) return -1;

	int Highest = TNumericLimits<int>::Lowest();
	for (const auto& Pair : Items)
	{
		if (Pair.Key > Highest)
		{
			Highest = Pair.Key;
		}
	}
	return Highest;
}

void UPrioritySystem::HandleItemAdded(const FInstancedStruct& Item)
{
}

void UPrioritySystem::HandleItemRemoved(const FInstancedStruct& Item)
{
}

void UPrioritySystem::HandleItemChanged(const FInstancedStruct& Item)
{
}

