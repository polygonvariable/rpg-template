#include "Game/Interact/InteractActor.h"

#include "GameFramework/HUD.h"
#include "Game/Interact/InteractComponent.h"

FInteractItem& AInteractActor::GetInteractItem()
{
	return InteractItem;
}

void AInteractActor::Interact_Implementation()
{
	OnInteracted();
}


void AInteractActor::BuildItem_Implementation()
{
	InteractItem.UUID = GUID;
	InteractItem.Name = Name;
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
	if(UInteractComponent* InteractComponent = GetInteractComponent())
	{
		InteractComponent->AddItem(this);
	}
}

void AInteractActor::EndInteract_Implementation()
{
	if (UInteractComponent* InteractComponent = GetInteractComponent())
	{
		InteractComponent->RemoveItem(this);
	}
}

void AInteractActor::UpdateItem_Implementation()
{
	BuildItem();
	OnItemUpdated.Broadcast(InteractItem);
}

void AInteractActor::OnInteracted_Implementation()
{
}


void AInteractActor::BeginStage_Implementation(FInstancedStruct Parameters)
{
	BuildItem();
}

void AInteractActor::EndStage_Implementation(const EEndPlayReason::Type EndPlayReason)
{
	EndInteract();
}

void AInteractActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Execute_EndStage(this, EndPlayReason);
	Super::EndPlay(EndPlayReason);
}
