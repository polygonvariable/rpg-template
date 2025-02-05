// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "InteractWidget.h"

// Engine Headers
#include "GameFramework/HUD.h"

// Project Headers
#include "RenShared/Public/Macro/LogMacro.h"
#include "InteractActor.h"
#include "InteractComponent.h"


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
	if (!IsValid(PlayerController))
	{
		LOG_ERROR(this, LogTemp, "PlayerController is not valid");
		return;
	}

	AHUD* HUD = PlayerController->GetHUD();
	if (!IsValid(HUD))
	{
		LOG_ERROR(this, LogTemp, "HUD is not valid");
		return;
	}

	UInteractComponent* InteractComponent = Cast<UInteractComponent>(HUD->GetComponentByClass(UInteractComponent::StaticClass()));
	if (!IsValid(InteractComponent))
	{
		LOG_ERROR(this, LogTemp, "InteractComponent is not valid");
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

void UInteractWidget::AddItem_Implementation(AActor* Actor)
{
	if (!InteractActors.Contains(Actor))
	{
		InteractActors.Add(Actor);
		OnItemAdded(Actor);
	}
}

void UInteractWidget::RemoveItem_Implementation(AActor* Actor)
{
	if (InteractActors.Contains(Actor))
	{
		InteractActors.Remove(Actor);
		OnItemRemoved(Actor);
	}
}

void UInteractWidget::OnItemAdded_Implementation(AActor* Actor) {}
void UInteractWidget::OnItemRemoved_Implementation(AActor* Actor) {}


void UInteractWidget::OnInteractStarted_Implementation(AActor* Actor)
{
	if (IsValid(Actor))
	{
		AddItem(Actor);
	}
}

void UInteractWidget::OnInteractEnded_Implementation(AActor* Actor)
{
	if (IsValid(Actor))
	{
		RemoveItem(Actor);
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
	if (!IsValid(Object))
	{
		return false;
	}

	InteractActor = Cast<AInteractActor>(Object);
	if (!IsValid(InteractActor))
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
	if (IsValid(InteractActor))
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
	if (IsValid(InteractActor))
	{
		InteractActor->OnItemUpdated.RemoveDynamic(this, &UInteractEntryWidget::OnItemUpdated);
		InteractActor = nullptr;
	}
}

