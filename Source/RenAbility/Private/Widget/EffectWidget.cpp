// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Widget/EffectWidget.h"

// Engine Headers
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/PanelWidget.h"

// Project Headers
#include "RenAbility/Public/AbilityComponent.h"
#include "RenGlobal/Public/Macro/LogMacro.h"




void UEffectCollectionEntryWidget::RegisterASC(UAbilitySystemComponent* TargetASC, const FGameplayEffectSpec& SpecApplied, const FActiveGameplayEffectHandle& ActiveHandle)
{
	if (IsValid(TargetASC) && !ASC.IsValid() && ActiveHandle.IsValid())
	{
		ASC = TargetASC;

		ASC->OnGameplayEffectStackChangeDelegate(ActiveHandle)->AddUObject(this, &UEffectCollectionEntryWidget::HandleEffectStackChanged);
		ASC->OnGameplayEffectRemoved_InfoDelegate(ActiveHandle)->AddUObject(this, &UEffectCollectionEntryWidget::HandleEffectRemoved);

		HandleEffectStackChanged(ActiveHandle, SpecApplied.GetStackCount(), 0);

		CurrentActiveHandle = ActiveHandle;
	}
}

void UEffectCollectionEntryWidget::HandleEffectStackChanged_Implementation(FActiveGameplayEffectHandle EffectHandle, int32 NewStackCount, int32 PreviousStackCount)
{
	if (IsValid(StackTextBlock))
	{
		StackTextBlock->SetText(FText::AsNumber(NewStackCount));
	}
}

void UEffectCollectionEntryWidget::HandleEffectRemoved_Implementation(const FGameplayEffectRemovalInfo& EffectRemovalInfo)
{
	const FActiveGameplayEffect* ActiveEffect = EffectRemovalInfo.ActiveEffect;
	if (ActiveEffect && ActiveEffect->Handle.IsValid() && ASC.IsValid())
	{
		if (FOnActiveGameplayEffectStackChange* StackDelegate = ASC->OnGameplayEffectStackChangeDelegate(ActiveEffect->Handle))
		{
			StackDelegate->RemoveAll(this);
		}

		if (FOnActiveGameplayEffectRemoved_Info* EffectDelegate = ASC->OnGameplayEffectRemoved_InfoDelegate(ActiveEffect->Handle))
		{
			EffectDelegate->RemoveAll(this);
		}
	}

	this->RemoveFromParent();
}

void UEffectCollectionEntryWidget::HandleEffectTimeChanged_Implementation()
{
	float Duration = 0.0f;
	float RemainingTime = 0.0f;

	GetEffectDurationAndRemainingTime(Duration, RemainingTime);

	if (IsValid(DurationProgressBar))
	{
		DurationProgressBar->SetPercent(RemainingTime / Duration);
	}

	if (IsValid(DurationTextBlock))
	{
		DurationTextBlock->SetText(FText::AsNumber(RemainingTime, &FormatOptions));
	}
}

void UEffectCollectionEntryWidget::GetEffectDurationAndRemainingTime(float& Duration, float& RemainingTime)
{
	Duration = 0.0f;
	RemainingTime = 0.0f;

	if (ASC.IsValid() && CurrentActiveHandle.IsValid())
	{
		if (const FActiveGameplayEffect* ActiveEffect = ASC->GetActiveGameplayEffect(CurrentActiveHandle))
		{
			Duration = ActiveEffect->GetDuration();
			RemainingTime = ActiveEffect->GetTimeRemaining(ASC->GetWorld()->GetTimeSeconds());
		}
	}
}

void UEffectCollectionEntryWidget::NativeConstruct()
{
	FormatOptions.MinimumIntegralDigits = 1;
	FormatOptions.MinimumFractionalDigits = 1;
	FormatOptions.MaximumFractionalDigits = 1;

	Super::NativeConstruct();
}

void UEffectCollectionEntryWidget::NativeDestruct()
{
	if (ASC.IsValid())
	{
		if (CurrentActiveHandle.IsValid())
		{
			if (FOnActiveGameplayEffectStackChange* StackDelegate = ASC->OnGameplayEffectStackChangeDelegate(CurrentActiveHandle))
			{
				StackDelegate->RemoveAll(this);
			}

			if (FOnActiveGameplayEffectRemoved_Info* EffectDelegate = ASC->OnGameplayEffectRemoved_InfoDelegate(CurrentActiveHandle))
			{
				EffectDelegate->RemoveAll(this);
			}
		}

		ASC.Reset();
	}

	Super::NativeDestruct();
}



void UEffectCollectionWidget::RegisterASC(AActor* Actor)
{
	CleanUpASC();

	if (!IsValid(Actor))
	{
		LOG_ERROR(LogTemp, TEXT("Actor is not valid"));
		return;
	}

	ASC = Actor->GetComponentByClass<UAbilitySystemComponent>();
	if (!ASC.IsValid())
	{
		LOG_ERROR(LogTemp, TEXT("AbilitySystemComponent is not valid"));
		return;
	}

	ASC->OnActiveGameplayEffectAddedDelegateToSelf.AddUObject(this, &UEffectCollectionWidget::OnEffectAdded);
	ASC->OnAnyGameplayEffectRemovedDelegate().AddUObject(this, &UEffectCollectionWidget::OnEffectRemoved);
}

void UEffectCollectionWidget::OnEffectAdded(UAbilitySystemComponent* Target, const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle)
{
	FGameplayTagContainer AssetTags;
	SpecApplied.GetAllAssetTags(AssetTags);

	if (!AssetTags.HasTagExact(CaptureEffectTag))
	{
		return;
	}

	HandleEffectAdded(SpecApplied, ActiveHandle);
}

void UEffectCollectionWidget::OnEffectRemoved(const FActiveGameplayEffect& EffectRemoved)
{
	FGameplayTagContainer AssetTags;
	EffectRemoved.Spec.GetAllAssetTags(AssetTags);

	if (!AssetTags.HasTagExact(CaptureEffectTag))
	{
		return;
	}

	HandleEffectRemoved(EffectRemoved);
}

void UEffectCollectionWidget::HandleEffectAdded_Implementation(const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle)
{
	if (IsValid(EffectStackPanel) && IsValid(EntryWidgetClass) && ASC.IsValid())
	{
		UEffectCollectionEntryWidget* EntryWidget = CreateWidget<UEffectCollectionEntryWidget>(this, EntryWidgetClass);
		if (IsValid(EntryWidget))
		{
			EntryWidget->RegisterASC(ASC.Get(), SpecApplied, ActiveHandle);
			EffectStackPanel->AddChild(EntryWidget);
		}
	}
}

void UEffectCollectionWidget::HandleEffectRemoved_Implementation(const FActiveGameplayEffect& EffectRemoved)
{

}

void UEffectCollectionWidget::CleanUpASC()
{
	if (ASC.IsValid())
	{
		ASC->OnActiveGameplayEffectAddedDelegateToSelf.RemoveAll(this);
		ASC->OnAnyGameplayEffectRemovedDelegate().RemoveAll(this);
		ASC.Reset();
	}
}

void UEffectCollectionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (APlayerController* PlayerController = GetOwningPlayer())
	{
		PlayerController->GetOnNewPawnNotifier().AddWeakLambda(this, [&](APawn* NewPawn) { RegisterASC(NewPawn); });

		if (APawn* ExistingPawn = PlayerController->GetPawn())
		{
			RegisterASC(ExistingPawn);
		}
	}
	else
	{
		LOG_ERROR(LogTemp, TEXT("PlayerController is not valid"));
	}
}

void UEffectCollectionWidget::NativeDestruct()
{
	CleanUpASC();

	if (APlayerController* PlayerController = GetOwningPlayer())
	{
		PlayerController->GetOnNewPawnNotifier().RemoveAll(this);
	}

	Super::NativeDestruct();
}



void UEffectDurationTagWidget::RegisterActor(AActor* Actor)
{
	if (ASC.IsValid())
	{
		ASC->RegisterGameplayTagEvent(CaptureDurationTag, EGameplayTagEventType::NewOrRemoved).RemoveAll(this);
		ASC.Reset();
	}

	if (!IsValid(Actor))
	{
		LOG_ERROR(LogTemp, TEXT("Actor or CaptureDurationTag is not valid"));
		return;
	}

	ASC = Actor->GetComponentByClass<UAbilityComponent>();
	if (!ASC.IsValid())
	{
		LOG_ERROR(LogTemp, TEXT("AbilitySystemComponent is not valid"));
		return;
	}

	ASC->RegisterGameplayTagEvent(CaptureDurationTag, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &UEffectDurationTagWidget::OnTagCountChanged);
}

void UEffectDurationTagWidget::OnTagCountChanged(const FGameplayTag CooldownTag, int32 NewCount)
{
	if (NewCount > 0)
	{
		HandleEffectTimeChanged();
	}
}

void UEffectDurationTagWidget::HandleEffectTimeChanged_Implementation()
{
	float Duration = 0.0f;
	float RemainingTime = 0.0f;

	GetEffectDurationAndRemainingTime(Duration, RemainingTime);

	if (IsValid(DurationProgressBar))
	{
		DurationProgressBar->SetPercent(RemainingTime / Duration);
	}

	if (IsValid(DurationTextBlock))
	{
		DurationTextBlock->SetText(FText::AsNumber(RemainingTime, &FormatOptions));
	}
}

void UEffectDurationTagWidget::GetEffectDurationAndRemainingTime(float& Duration, float& RemainingTime)
{
	Duration = 0.0f;
	RemainingTime = 0.0f;

	if (ASC.IsValid())
	{
		const FGameplayEffectQuery Query = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(DurationTags);
		TArray<TPair<float, float>> TimeRemainingAndDuration = ASC->GetActiveEffectsTimeRemainingAndDuration(Query);

		float LongestRemaining = 0.f;
		float LongestDuration = 0.f;

		for (const TPair<float, float>& Pair : TimeRemainingAndDuration)
		{
			if (Pair.Key > LongestRemaining)
			{
				LongestRemaining = Pair.Key;
				LongestDuration = Pair.Value;
			}
		}

		Duration = LongestDuration;
		RemainingTime = LongestRemaining;
	}
}

void UEffectDurationTagWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FormatOptions.MinimumIntegralDigits = 1;
	FormatOptions.MinimumFractionalDigits = 1;
	FormatOptions.MaximumFractionalDigits = 1;

	DurationTags.AddTag(CaptureDurationTag);

	if (APlayerController* PlayerController = GetOwningPlayer())
	{
		PlayerController->GetOnNewPawnNotifier().AddWeakLambda(this, [&](APawn* NewPawn) { RegisterActor(NewPawn); });

		if (APawn* ExistingPawn = PlayerController->GetPawn())
		{
			RegisterActor(ExistingPawn);
		}
	}
	else
	{
		LOG_ERROR(LogTemp, TEXT("PlayerController is not valid"));
	}
}

void UEffectDurationTagWidget::NativeDestruct()
{
	if (ASC.IsValid())
	{
		ASC->RegisterGameplayTagEvent(CaptureDurationTag, EGameplayTagEventType::NewOrRemoved).RemoveAll(this);
		ASC.Reset();
	}

	Super::NativeDestruct();
}
