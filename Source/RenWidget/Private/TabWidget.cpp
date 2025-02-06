// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "TabWidget.h"

// Engine Headers
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/PanelWidget.h"

// Project Headers
#include "RenShared/Public/Macro/LogMacro.h"


void UTabControl::Select_Implementation(bool bSelected)
{
	bIsSelected = bSelected;
}

void UTabControl::HandleSelection_Implementation()
{
	OnSelect.Broadcast(this);
}

void UTabControl::NativeConstruct()
{
	if (IsValid(TabButton))
	{
		TabButton->OnClicked.AddDynamic(this, &UTabControl::HandleSelection);
	}
	if (IsValid(TabText))
	{
		TabText->SetText(Title);
	}
}


void UTabBoxControl::BuildTabs_Implementation(const TSet<FName>& Items)
{
	if(!TabClass || !TabClass->IsChildOf(UTabControl::StaticClass()))
	{
		LOG_ERROR(this, LogTemp, "TabClass must be child of UTabControl");
		return;
	}
	
	for (FName Item : Items)
	{
		UWidget* TabItem = CreateWidget<UTabControl>(this, TabClass);
		if (!TabItem)
		{
			continue;
		}

		UTabControl* Tab = Cast<UTabControl>(TabItem);
		if (!Tab)
		{
			continue;
		}

		Tab->Title = FText::FromString(Item.ToString());
		Tab->OnSelect.RemoveAll(this);
		Tab->OnSelect.AddDynamic(this, &UTabBoxControl::OnTabSelected);

		HandleTab(Tab);
	}
}

void UTabBoxControl::ClearTabs_Implementation()
{
	if (!IsValid(TabContainer))
	{
		LOG_ERROR(this, LogTemp, "TabContainer is null");
		return;
	}
	TabContainer->ClearChildren();
}

void UTabBoxControl::OnTabSelected_Implementation(UTabControl* Tab)
{
	if (!IsValid(Tab) || !IsValid(TabContainer))
	{
		LOG_ERROR(this, LogTemp, "Tab or TabContainer is null");
		return;
	}

	TArray<UWidget*> Tabs = TabContainer->GetAllChildren();
	for (UWidget* RawTab : Tabs)
	{
		UTabControl* ResolvedTab = Cast<UTabControl>(RawTab);
		if (!ResolvedTab)
		{
			continue;
		}
		ResolvedTab->Select(RawTab == Tab);
	}

	OnTabChanged.Broadcast(FName(Tab->Title.ToString()));
}

void UTabBoxControl::HandleTab_Implementation(UTabControl* Tab) {
	if (!IsValid(TabContainer))
	{
		LOG_ERROR(this, LogTemp, "TabContainer is null");
		return;
	}
	TabContainer->AddChild(Tab);
}