#include "Features/Interact/InteractWidget.h"

#include "GameFramework/HUD.h"
#include "Internal/InternalMacro.h"
#include "Features/Interact/InteractActor.h"
#include "Features/Interact/InteractComponent.h"


void UInteractWidget::RegisterInteract_Implementation()
{
	HandleComponentBinding(false);
}

void UInteractWidget::UnregisterInteract_Implementation()
{
	HandleComponentBinding(true);
}

void UInteractWidget::HandleComponentBinding_Implementation(bool bIsUnbind)
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController)
	{
		LOG_ERROR(LogTemp, this, "PlayerController not found");
		return;
	}

	AHUD* HUD = PlayerController->GetHUD();
	if (!HUD)
	{
		LOG_ERROR(LogTemp, this, "HUD not found");
		return;
	}

	UInteractComponent* InteractComponent = Cast<UInteractComponent>(HUD->GetComponentByClass(UInteractComponent::StaticClass()));
	if (!InteractComponent)
	{
		LOG_ERROR(LogTemp, this, "InteractComponent not found");
		return;
	}

	if (!bIsUnbind)
	{
		if (!InteractComponent->OnInteractStarted.IsBound() && !InteractComponent->OnInteractEnded.IsBound())
		{
			InteractComponent->OnInteractStarted.AddDynamic(this, &UInteractWidget::OnInteractStarted);
			InteractComponent->OnInteractEnded.AddDynamic(this, &UInteractWidget::OnInteractEnded);
		}
	}
	else {
		InteractComponent->OnInteractStarted.RemoveDynamic(this, &UInteractWidget::OnInteractStarted);
		InteractComponent->OnInteractEnded.RemoveDynamic(this, &UInteractWidget::OnInteractEnded);
	}
}

void UInteractWidget::AddItem_Implementation(AActor* Item)
{
	if(!InteractActorsSet.Contains(Item))
	{
		InteractActorsSet.Add(Item);
		OnItemAdded(Item);
	}
}

void UInteractWidget::RemoveItem_Implementation(AActor* Item)
{
	if(InteractActorsSet.Contains(Item))
	{
		InteractActorsSet.Remove(Item);
		OnItemRemoved(Item);
	}
}

void UInteractWidget::OnItemAdded_Implementation(AActor* Item) {}
void UInteractWidget::OnItemRemoved_Implementation(AActor* Item) {}


void UInteractWidget::OnInteractStarted_Implementation(AActor* Item)
{
	if (Item)
	{
		AddItem(Item);
	}
}

void UInteractWidget::OnInteractEnded_Implementation(AActor* Item)
{
	if (Item)
	{
		RemoveItem(Item);
	}
}

void UInteractWidget::NativeConstruct()
{
	Super::NativeConstruct();
	RegisterInteract();
}

void UInteractWidget::NativeDestruct()
{
	UnregisterInteract();
	Super::NativeDestruct();
}


bool UInteractEntryWidget::InitializeItem_Implementation(UObject* Object)
{
	if (!Object)
	{
		return false;
	}

	InteractActor = Cast<AInteractActor>(Object);
	if (!InteractActor)
	{
		return false;
	}

	InteractActor->OnItemUpdated.RemoveDynamic(this, &UInteractEntryWidget::OnItemUpdated);
	InteractActor->OnItemUpdated.AddDynamic(this, &UInteractEntryWidget::OnItemUpdated);

	InteractItem = InteractActor->GetInteractItem();

	return true;
}

void UInteractEntryWidget::Interact_Implementation()
{
	if (InteractActor)
	{
		InteractActor->Interact();
	}
}

void UInteractEntryWidget::OnItemUpdated_Implementation(FInteractItem Item)
{
	InteractItem = Item;
}

void UInteractEntryWidget::NativeDestruct()
{
	if (InteractActor)
	{
		InteractActor->OnItemUpdated.RemoveDynamic(this, &UInteractEntryWidget::OnItemUpdated);
		InteractActor = nullptr;
	}
}
