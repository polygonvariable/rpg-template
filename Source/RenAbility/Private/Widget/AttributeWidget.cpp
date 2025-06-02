// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Widget/AttributeWidget.h"

// Engine Headers
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/PanelWidget.h"

// Project Headers
#include "RenAbility/Public/AbilityComponent.h"
#include "RenGlobal/Public/Macro/LogMacro.h"




void UAttributeClampedWidget::HandleValueChanged_Implementation()
{
	if (IsValid(ValueProgressBar))
	{
		ValueProgressBar->SetPercent(CurrentMax > 0.0f ? (CurrentValue / CurrentMax) : 0.0f);
	}

	if (IsValid(ValueTextBlock))
	{
		FText FormattedText = FText::Format(
			FText::FromString("{0} / {1}"),
			FText::AsNumber(CurrentValue),
			FText::AsNumber(CurrentMax)
		);

		ValueTextBlock->SetText(FormattedText);
	}
}



void UAttributeClampedWidget::RegisterActor(AActor* Actor)
{
	if (BaseASC.IsValid())
	{
		BaseASC->GetGameplayAttributeValueChangeDelegate(BaseAttribute).RemoveAll(this);
		BaseASC->GetGameplayAttributeValueChangeDelegate(MaxAttribute).RemoveAll(this);
		BaseASC->OnAggregatedRefresh.RemoveAll(this);
		BaseASC.Reset();
	}

	if (!IsValid(Actor))
	{
		LOG_ERROR(LogTemp, TEXT("Actor is not valid"));
		return;
	}

	BaseASC = Actor->GetComponentByClass<UAbilityComponent>();
	if (!BaseASC.IsValid())
	{
		LOG_ERROR(LogTemp, TEXT("AbilitySystemComponent is not valid"));
		return;
	}

	CurrentValue = BaseASC->GetAggregatedNumericAttribute(BaseAttribute);
	CurrentMax = BaseASC->GetAggregatedNumericAttribute(MaxAttribute);
	HandleValueChanged();

	BaseASC->GetGameplayAttributeValueChangeDelegate(BaseAttribute).AddWeakLambda(this, [&](const FOnAttributeChangeData& Data) { OnAggregatedRefresh(); });
	BaseASC->GetGameplayAttributeValueChangeDelegate(MaxAttribute).AddWeakLambda(this, [&](const FOnAttributeChangeData& Data) { OnAggregatedRefresh(); });
	BaseASC->OnAggregatedRefresh.AddDynamic(this, &UAttributeClampedWidget::OnAggregatedRefresh);
}



void UAttributeClampedWidget::OnAggregatedRefresh()
{
	if (!BaseASC.IsValid())
	{
		LOG_ERROR(LogTemp, TEXT("AbilitySystemComponent is not valid"));
		return;
	}

	CurrentValue = BaseASC->GetAggregatedNumericAttribute(BaseAttribute);
	CurrentMax = BaseASC->GetAggregatedNumericAttribute(MaxAttribute);
	HandleValueChanged();
}


void UAttributeClampedWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (IsValid(TitleTextBlock))
	{
		TitleTextBlock->SetText(FText::Format(FText::FromString("{0}:"), Title));
	}
}

void UAttributeClampedWidget::NativeConstruct()
{
	Super::NativeConstruct();

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

void UAttributeClampedWidget::NativeDestruct()
{
	if (BaseASC.IsValid())
	{
		BaseASC->GetGameplayAttributeValueChangeDelegate(BaseAttribute).RemoveAll(this);
		BaseASC->GetGameplayAttributeValueChangeDelegate(MaxAttribute).RemoveAll(this);
		BaseASC.Reset();
	}

	if (APlayerController* PlayerController = GetOwningPlayer())
	{
		PlayerController->GetOnNewPawnNotifier().RemoveAll(this);
	}

	Super::NativeDestruct();
}






void UAttributeScalarWidget::HandleValueChanged_Implementation()
{
	if (IsValid(ValueTextBlock))
	{
		ValueTextBlock->SetText(FText::AsNumber(CurrentValue));
	}
}



void UAttributeScalarWidget::RegisterActor(AActor* Actor)
{
	if (BaseASC.IsValid())
	{
		BaseASC->GetGameplayAttributeValueChangeDelegate(BaseAttribute).RemoveAll(this);
		BaseASC->OnAggregatedRefresh.RemoveAll(this);
		BaseASC.Reset();
	}

	if (!IsValid(Actor))
	{
		LOG_ERROR(LogTemp, TEXT("Actor is not valid"));
		return;
	}

	BaseASC = Actor->GetComponentByClass<UAbilityComponent>();
	if (!BaseASC.IsValid())
	{
		LOG_ERROR(LogTemp, TEXT("AbilitySystemComponent is not valid"));
		return;
	}

	CurrentValue = BaseASC->GetAggregatedNumericAttribute(BaseAttribute);
	HandleValueChanged();

	BaseASC->GetGameplayAttributeValueChangeDelegate(BaseAttribute).AddWeakLambda(this, [&](const FOnAttributeChangeData& Data) { OnAggregatedRefresh(); });
	BaseASC->OnAggregatedRefresh.AddDynamic(this, &UAttributeScalarWidget::OnAggregatedRefresh);
}

void UAttributeScalarWidget::OnAggregatedRefresh()
{
	if (!BaseASC.IsValid())
	{
		LOG_ERROR(LogTemp, TEXT("AbilitySystemComponent is not valid"));
		return;
	}

	CurrentValue = BaseASC->GetAggregatedNumericAttribute(BaseAttribute);
	HandleValueChanged();
}



void UAttributeScalarWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (IsValid(TitleTextBlock))
	{
		TitleTextBlock->SetText(FText::Format(FText::FromString("{0}:"), Title));
	}
}

void UAttributeScalarWidget::NativeConstruct()
{
	Super::NativeConstruct();

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

void UAttributeScalarWidget::NativeDestruct()
{
	if (BaseASC.IsValid())
	{
		BaseASC->GetGameplayAttributeValueChangeDelegate(BaseAttribute).RemoveAll(this);
		BaseASC->OnAggregatedRefresh.RemoveAll(this);
		BaseASC.Reset();
	}

	if (APlayerController* PlayerController = GetOwningPlayer())
	{
		PlayerController->GetOnNewPawnNotifier().RemoveAll(this);
	}

	Super::NativeDestruct();
}

