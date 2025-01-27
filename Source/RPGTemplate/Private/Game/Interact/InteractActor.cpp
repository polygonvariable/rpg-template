#include "Game/Interact/InteractActor.h"

AInteractActor::AInteractActor() : AEActor()
{

	InteractItem.UUID = UUID;
	InteractItem.Name = Name;
	InteractItem.Target = this;

}

UInteractComponent* AInteractActor::GetInteractComponent_Implementation() const
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController()) {
		if (AHUD* HUD = PlayerController->GetHUD()) {
			return Cast<UInteractComponent>(HUD->GetComponentByClass(UInteractComponent::StaticClass()));
		}
	}
	return nullptr;
}

void AInteractActor::StartInteract_Implementation()
{
	if(UInteractComponent* interactComponent = GetInteractComponent())
	{
		interactComponent->AddItem(InteractItem);
	}
}

void AInteractActor::EndInteract_Implementation()
{
	if (UInteractComponent* interactComponent = GetInteractComponent())
	{
		interactComponent->RemoveItem(InteractItem);
	}
}
