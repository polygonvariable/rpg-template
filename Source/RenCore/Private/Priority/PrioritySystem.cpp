// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Priority/PrioritySystem.h"
#include "RenGlobal/Public/Macro/LogMacro.h"


void UPrioritySystem::AddItem(FInstancedStruct Item, int Priority)
{
	if (!Item.IsValid() || Priority < 0)
	{
		LOG_ERROR(LogTemp, TEXT("Item is not valid or priority is less than 0"));
		return;
	}

	const int HighestPriority = GetHighestPriority();

	Items.Add(Priority, Item);
	HandleItemAdded(Item);
	OnItemAdded.Broadcast(Item);

	if (Priority > HighestPriority)
	{
		ActiveItem = Item;
		HandleItemChanged(ActiveItem);
		OnItemChanged.Broadcast(ActiveItem);
	}
	else
	{
		LOG_WARNING(LogTemp, TEXT("Priority is less than highest priority, added in queue"));
	}
}

void UPrioritySystem::RemoveItem(int Priority)
{
	FInstancedStruct* Item = Items.Find(Priority);
	if (!Item)
	{
		LOG_WARNING(LogTemp, TEXT("Item not found"));
		return;
	}

	int HighestPriority = GetHighestPriority();
	
	Items.Remove(Priority);
	HandleItemRemoved(*Item);
	OnItemRemoved.Broadcast(*Item);

	if (Priority != HighestPriority)
	{
		return;
	}

	int NewPriority = GetHighestPriority();
	if (FInstancedStruct* NewItem = Items.Find(NewPriority))
	{
		ActiveItem = *NewItem;
		if (ActiveItem.IsValid())
		{
			HandleItemChanged(ActiveItem);
			OnItemChanged.Broadcast(ActiveItem);
		}
	}
}

int UPrioritySystem::GetHighestPriority() const
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

