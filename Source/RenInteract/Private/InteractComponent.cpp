// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "InteractComponent.h"


void UInteractComponent::AddItem_Implementation(AActor* Item)
{
	if (Item)
	{
		OnInteractStarted.Broadcast(Item);
	}
}

void UInteractComponent::RemoveItem_Implementation(AActor* Item)
{
	if(Item)
	{
		OnInteractEnded.Broadcast(Item);
	}
}

