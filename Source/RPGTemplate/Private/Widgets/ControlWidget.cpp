#include "Widgets/ControlWidget.h"

#include "Internal/InternalMacro.h"


void UTabControl::HandleSelected_Implementation(bool bWasSelected)
{
	bIsSelected = bWasSelected;
}

void UTabControl::Select_Implementation()
{
	OnSelect.Broadcast(this);
}

void UTabControl::NativeConstruct()
{
	if (TabButton)
	{
		TabButton->OnClicked.AddDynamic(this, &UTabControl::Select);
	}
}


UTabBoxControl::UTabBoxControl(const FObjectInitializer& ObjectInitializer) : UUserWidget(ObjectInitializer) {}

void UTabBoxControl::BuildTabs_Implementation(const TSet<FName>& Items)
{
	if(!TabClass || !TabClass->IsChildOf(UTabControl::StaticClass()))
	{
		LOG_ERROR(LogTemp, this, "TabClass must be child of UTabControl");
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
	if (!TabContainer)
	{
		LOG_ERROR(LogTemp, this, "TabContainer is null");
		return;
	}
	TabContainer->ClearChildren();
}

void UTabBoxControl::OnTabSelected_Implementation(UTabControl* Tab)
{
	if (!Tab || !TabContainer)
	{
		LOG_ERROR(LogTemp, this, "Tab or TabContainer is null");
		return;
	}

	TArray<UWidget*> Tabs = TabContainer->GetAllChildren();
	for (UWidget* RawTab : Tabs)
	{
		UTabControl* ResolvedTab = Cast<UTabControl>(RawTab);
		ResolvedTab->HandleSelected(RawTab == Tab);
	}

	OnTabChanged.Broadcast(FName(Tab->Title.ToString()));
}

void UTabBoxControl::HandleTab_Implementation(UTabControl* Tab) {
	if (!TabContainer)
	{
		LOG_ERROR(LogTemp, this, "TabContainer is null");
		return;
	}
	TabContainer->AddChild(Tab);
}
