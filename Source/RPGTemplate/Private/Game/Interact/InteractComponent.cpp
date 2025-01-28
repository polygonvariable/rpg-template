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


void UInteractComponent::AddItem_Implementation(AActor* Item)
{
	if (Item) {
		OnInteractStarted.Broadcast(Item);
	}
}

void UInteractComponent::RemoveItem_Implementation(AActor* Item)
{
	if(Item) {
		OnInteractEnded.Broadcast(Item);
	}
}
