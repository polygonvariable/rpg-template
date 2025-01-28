#include "Game/Interact/InteractWidget.h"

void UInteractWidget::NativeConstruct()
{
	Super::NativeConstruct();
	InitializeStage();
}

void UInteractWidget::NativeDestruct()
{
	EndStage();
	Super::NativeDestruct();
}

void UInteractWidget::InitializeStage_Implementation()
{
	BindToInteractComponent(false);
}

void UInteractWidget::EndStage_Implementation()
{
	BindToInteractComponent(true);
}

void UInteractWidget::BindToInteractComponent_Implementation(bool bIsUnbind)
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController()) {
		if (AHUD* HUD = PlayerController->GetHUD()) {

			UInteractComponent* InteractComponent = Cast<UInteractComponent>(HUD->GetComponentByClass(UInteractComponent::StaticClass()));
			
			if(!bIsUnbind) {
				if (!InteractComponent->OnInteractStarted.IsBound() && !InteractComponent->OnInteractEnded.IsBound()) {
					InteractComponent->OnInteractStarted.AddDynamic(this, &UInteractWidget::OnInteractStarted);
					InteractComponent->OnInteractEnded.AddDynamic(this, &UInteractWidget::OnInteractEnded);
				}
			}
			else {
				InteractComponent->OnInteractStarted.RemoveDynamic(this, &UInteractWidget::OnInteractStarted);
				InteractComponent->OnInteractEnded.RemoveDynamic(this, &UInteractWidget::OnInteractEnded);
			}

		}
	}
}

void UInteractWidget::AddItem_Implementation(AActor* Item)
{
	if(!InteractActorsSet.Contains(Item)) {
		InteractActorsSet.Add(Item);
		OnItemAdded(Item);
	}
}

void UInteractWidget::RemoveItem_Implementation(AActor* Item)
{
	if(InteractActorsSet.Contains(Item)) {
		InteractActorsSet.Remove(Item);
		OnItemRemoved(Item);
	}
}

void UInteractWidget::OnItemAdded_Implementation(AActor* Item)
{
}

void UInteractWidget::OnItemRemoved_Implementation(AActor* Item)
{
}


void UInteractWidget::OnInteractStarted_Implementation(AActor* Item)
{
	if (Item) {
		AddItem(Item);
	}
}

void UInteractWidget::OnInteractEnded_Implementation(AActor* Item)
{
	if (Item) {
		RemoveItem(Item);
	}
}