#include "Features/Interact/InteractComponent.h"


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
