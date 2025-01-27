#include "Game/Interact/InteractWidget.h"

void UInteractWidget::BindToInteractComponent_Implementation()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController()) {
		if (AHUD* HUD = PlayerController->GetHUD()) {

			UInteractComponent* InteractComponent = Cast<UInteractComponent>(HUD->GetComponentByClass(UInteractComponent::StaticClass()));
			
			InteractComponent->OnItemAdded.AddDynamic(this, &UInteractWidget::OnItemAdded);
			InteractComponent->OnItemRemoved.AddDynamic(this, &UInteractWidget::OnItemRemoved);

		}
	}
}

UObject* UInteractWidget::AddItem_Implementation(FInteractItem Item)
{
	if (!InteractItems.Contains(Item.UUID)) {

		UObject* ItemObject = NewObject<UObject>(this);
		if (ItemObject) {

			InteractItems.Add(Item.UUID, ItemObject);
			return ItemObject;

		}

	}
	return nullptr;
}

void UInteractWidget::RemoveItem_Implementation(FInteractItem Item)
{
	if (UObject* ItemFound = *InteractItems.Find(Item.UUID)) {

		ItemFound->MarkAsGarbage();
		InteractItems.Remove(Item.UUID);

	}
}


void UInteractWidget::OnItemAdded_Implementation(FInteractItem Item)
{
	AddItem(Item);
}

void UInteractWidget::OnItemRemoved_Implementation(FInteractItem Item)
{
	RemoveItem(Item);
}
