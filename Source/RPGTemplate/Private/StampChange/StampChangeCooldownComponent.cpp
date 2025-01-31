#include "StampChange/StampChangeCooldownComponent.h"


void UStampChangeCooldownComponent::ActivateStage_Implementation()
{
	Super::ActivateStage_Implementation();
	if (HasChanged())
	{

		FDateTime ChangeDate;
		GetChangedDate(ChangeDate);

		if (bOnlyOnce)
		{
			OnStampChangeCooldownStatus.Broadcast(EStampChangeCooldownStatus::Once);
		}
		else {
			if (FDateTime::Now() >= (ChangeDate + CooldownTime))
			{
				OnStampChangeCooldownStatus.Broadcast(EStampChangeCooldownStatus::Completed);
			}
			else
			{
				OnStampChangeCooldownStatus.Broadcast(EStampChangeCooldownStatus::Pending);
			}
		}
	}
	else
	{
		OnStampChangeCooldownStatus.Broadcast(EStampChangeCooldownStatus::NotFound);
	}
}
