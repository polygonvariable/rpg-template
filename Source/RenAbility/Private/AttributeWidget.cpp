// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "AttributeWidget.h"

// Engine Headers
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

// Project Headers
#include "RenGlobal/Public/Macro/LogMacro.h"




void UAttributeClampedWidget::HandleValueChanged_Implementation()
{
	if (IsValid(ValueProgressBar))
	{
		ValueProgressBar->SetPercent(CurrentMax > 0.0f ? (CurrentBase / CurrentMax) : 0.0f);
	}

	if (IsValid(ValueTextBlock))
	{
		FText FormattedText = FText::Format(
			FText::FromString("{0} / {1}"),
			FText::AsNumber(CurrentBase),
			FText::AsNumber(CurrentMax)
		);

		ValueTextBlock->SetText(FormattedText);
	}
}


void UAttributeClampedWidget::OnNewPawn(APawn* NewPawn)
{
	if (!IsValid(NewPawn))
	{
		LOG_ERROR(LogTemp, TEXT("Pawn is not valid"));
		return;
	}

	AbilityComponent = NewPawn->GetComponentByClass<UAbilitySystemComponent>();
	if (!IsValid(AbilityComponent))
	{
		LOG_ERROR(LogTemp, TEXT("AbilityComponent is not valid"));
		return;
	}

	CurrentBase = AbilityComponent->GetNumericAttribute(BaseAttribute);
	CurrentMax = AbilityComponent->GetNumericAttribute(MaxAttribute);
	HandleValueChanged();

	AbilityComponent->GetGameplayAttributeValueChangeDelegate(BaseAttribute).AddUObject(this, &UAttributeClampedWidget::OnBaseAttributeChanged);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(MaxAttribute).AddUObject(this, &UAttributeClampedWidget::OnMaxAttributeChanged);
}



void UAttributeClampedWidget::OnBaseAttributeChanged(const FOnAttributeChangeData& Data)
{
	CurrentBase = Data.NewValue;
	HandleValueChanged();
}

void UAttributeClampedWidget::OnMaxAttributeChanged(const FOnAttributeChangeData& Data)
{
	CurrentMax = Data.NewValue;
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
		PlayerController->GetOnNewPawnNotifier().AddUObject(this, &UAttributeClampedWidget::OnNewPawn);

		if (APawn* ExistingPawn = PlayerController->GetPawn())
		{
			OnNewPawn(ExistingPawn);
		}
	}
	else
	{
		LOG_ERROR(LogTemp, TEXT("PlayerController is not valid"));
	}
}

void UAttributeClampedWidget::NativeDestruct()
{
	if (IsValid(AbilityComponent))
	{
		AbilityComponent->GetGameplayAttributeValueChangeDelegate(BaseAttribute).RemoveAll(this);
		AbilityComponent->GetGameplayAttributeValueChangeDelegate(MaxAttribute).RemoveAll(this);
	}
	AbilityComponent = nullptr;

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
		ValueTextBlock->SetText(FText::AsNumber(CurrentBase));
	}
}


void UAttributeScalarWidget::OnNewPawn(APawn* NewPawn)
{
	if (!IsValid(NewPawn))
	{
		LOG_ERROR(LogTemp, TEXT("Pawn is not valid"));
		return;
	}

	AbilityComponent = NewPawn->GetComponentByClass<UAbilitySystemComponent>();
	if (!IsValid(AbilityComponent))
	{
		LOG_ERROR(LogTemp, TEXT("AbilityComponent is not valid"));
		return;
	}

	CurrentBase = AbilityComponent->GetNumericAttribute(BaseAttribute);
	HandleValueChanged();

	AbilityComponent->GetGameplayAttributeValueChangeDelegate(BaseAttribute).AddUObject(this, &UAttributeScalarWidget::OnBaseAttributeChanged);
}



void UAttributeScalarWidget::OnBaseAttributeChanged(const FOnAttributeChangeData& Data)
{
	CurrentBase = Data.NewValue;
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
		PlayerController->GetOnNewPawnNotifier().AddUObject(this, &UAttributeScalarWidget::OnNewPawn);

		if (APawn* ExistingPawn = PlayerController->GetPawn())
		{
			OnNewPawn(ExistingPawn);
		}
	}
	else
	{
		LOG_ERROR(LogTemp, TEXT("PlayerController is not valid"));
	}
}

void UAttributeScalarWidget::NativeDestruct()
{
	if (IsValid(AbilityComponent))
	{
		AbilityComponent->GetGameplayAttributeValueChangeDelegate(BaseAttribute).RemoveAll(this);
	}
	AbilityComponent = nullptr;

	if (APlayerController* PlayerController = GetOwningPlayer())
	{
		PlayerController->GetOnNewPawnNotifier().RemoveAll(this);
	}

	Super::NativeDestruct();
}

