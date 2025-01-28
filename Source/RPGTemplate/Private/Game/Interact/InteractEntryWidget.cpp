#include "Game/Interact/InteractEntryWidget.h"

bool UInteractEntryWidget::InitializeItem_Implementation(UObject* Object)
{
	if (!Object) {
		return false;
	}

	InteractActor = Cast<AInteractActor>(Object);
	if (!InteractActor) {
		return false;
	}

	InteractActor->OnItemUpdated.RemoveDynamic(this, &UInteractEntryWidget::OnItemUpdated);
	InteractActor->OnItemUpdated.AddDynamic(this, &UInteractEntryWidget::OnItemUpdated);

	InteractItem = InteractActor->GetInteractItem();

	return true;
}

void UInteractEntryWidget::Interact_Implementation()
{
	if (InteractActor) {
		InteractActor->Interact();
	}
}

void UInteractEntryWidget::OnItemUpdated_Implementation(FInteractItem Item)
{
	InteractItem = Item;
}

void UInteractEntryWidget::NativeDestruct()
{
	if (InteractActor) {
		InteractActor->OnItemUpdated.RemoveDynamic(this, &UInteractEntryWidget::OnItemUpdated);
		InteractActor = nullptr;
	}
}
