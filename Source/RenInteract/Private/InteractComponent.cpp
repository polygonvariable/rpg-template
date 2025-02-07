// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "InteractComponent.h"


UInteractComponent::UInteractComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInteractComponent::AddItem_Implementation(AActor* Actor)
{
	if (IsValid(Actor))
	{
		OnInteractStarted.Broadcast(Actor);
	}
}

void UInteractComponent::RemoveItem_Implementation(AActor* Actor)
{
	if (IsValid(Actor))
	{
		OnInteractEnded.Broadcast(Actor);
	}
}

