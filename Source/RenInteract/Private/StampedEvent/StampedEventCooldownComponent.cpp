// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "StampedEvent/StampedEventCooldownComponent.h"

// Project Headers
#include "RenShared/Public/Macro/LogMacro.h"


void UStampedEventCooldownComponent::ActivateStage_Implementation()
{
	Super::ActivateStage_Implementation();
	if (HasChanged()) {

		FDateTime EventDate;
		GetEventDate(EventDate);

		if (bOnlyOnce) {
			OnStampedEventCooldownStatus.Broadcast(EStampedEventCooldownStatus::Once);
		}
		else {
			if (FDateTime::Now() >= (EventDate + CooldownTime)) {
				OnStampedEventCooldownStatus.Broadcast(EStampedEventCooldownStatus::Completed);
			}
			else {
				OnStampedEventCooldownStatus.Broadcast(EStampedEventCooldownStatus::Pending);
			}
		}
	}
	else {
		OnStampedEventCooldownStatus.Broadcast(EStampedEventCooldownStatus::NotFound);
	}
}

