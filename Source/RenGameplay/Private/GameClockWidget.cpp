// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "GameClockWidget.h"

//
#include "GameClockSubsystem.h"
#include "RenGlobal/Public/Library/MiscLibrary.h"

// Engine Headers
#include "Components/TextBlock.h"


void UGameClockWidget::HandleClockTick(float Time)
{
	TimeTextBlock->SetText(FText::FromString(GameClockSubsystem->GetFormattedTimeOfDay()));
}

void UGameClockWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GameClockSubsystem = GetSubsystem<UGameClockSubsystem>(GetWorld());
	if (IsValid(TimeTextBlock) && IsValid(GameClockSubsystem))
	{
		GameClockSubsystem->OnTimeChanged.AddDynamic(this, &UGameClockWidget::HandleClockTick);
	}
}

void UGameClockWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

