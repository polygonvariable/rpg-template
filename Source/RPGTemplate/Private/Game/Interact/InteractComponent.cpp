#include "Game/Interact/InteractComponent.h"


UInteractComponent::UInteractComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UInteractComponent::AddItem_Implementation(FInteractItem Item)
{
	if (!Items.Contains(Item)) {
		Items.Add(Item);
		OnItemAdded.Broadcast(Item);
	}
}

void UInteractComponent::RemoveItem_Implementation(FInteractItem Item)
{
	if(Items.Contains(Item)) {
		Items.Remove(Item);
		OnItemRemoved.Broadcast(Item);
	}
}

bool UInteractComponent::ItemExists_Implementation(FInteractItem Item)
{
	return Items.Contains(Item);
}

