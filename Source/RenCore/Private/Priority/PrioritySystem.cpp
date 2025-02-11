// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Priority/PrioritySystem.h"
#include "RenShared/Public/Macro/LogMacro.h"


void UPrioritySystem::AddItem_Implementation(FInstancedStruct Item, const int Priority)
{
	if (!Item.IsValid() || Priority < 0)
	{
		LOG_ERROR(this, LogTemp, "Item is not valid or Priority is less than 0");
		return;
	}

	int HighestPriority = GetHighestPriority();

	Items.Add(Priority, Item);
	OnItemAdded.Broadcast(Item);

	if (Priority > HighestPriority)
	{
		ActiveItem = Item;
		OnItemChanged.Broadcast(ActiveItem);
	}
	else
	{
		LOG_WARNING(this, LogTemp, "Priority is less than highest priority, added in queue");
	}
}

void UPrioritySystem::RemoveItem_Implementation(const int Priority)
{
	if (FInstancedStruct* Item = Items.Find(Priority))
	{
		int CurrentPriority = GetHighestPriority();

		Items.Remove(Priority);
		OnItemRemoved.Broadcast(*Item);

		if (Priority != CurrentPriority)
		{
			return;
		}

		int NewPriority = GetHighestPriority();
		if (Items.Contains(NewPriority))
		{
			ActiveItem = Items.FindChecked(NewPriority);
			OnItemChanged.Broadcast(ActiveItem);
		}
	}
	else
	{
		LOG_WARNING(this, LogTemp, "Priority not found");
	}
}

int UPrioritySystem::GetHighestPriority()
{
	int HighestPriority = -1;

	TArray<int> Priorities;
	Items.GetKeys(Priorities);

	for (int Priority : Priorities)
	{
		if (Priority > HighestPriority)
		{
			HighestPriority = Priority;
		}
	}

	return HighestPriority;
}

