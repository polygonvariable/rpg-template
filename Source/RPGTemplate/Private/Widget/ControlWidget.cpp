#include "Widget/ControlWidget.h"

#include "Internal/InternalMacro.h"


void UTabControl::Select_Implementation()
{
	OnSelect.Broadcast(this);
}

void UTabControl::HandleSelected_Implementation(bool bSelected) {
	bIsSelected = bSelected;
}

UTabBoxControl::UTabBoxControl(const FObjectInitializer& ObjectInitializer) : UUserWidget(ObjectInitializer) {}

void UTabBoxControl::BuildTabs_Implementation(const TMap<FName, FText>& Items)
{
	if(!TabClass || !TabClass->IsChildOf(UTabControl::StaticClass())) {
		LOG_ERROR(LogTemp, this, "TabClass must be child of UTabControl");
		return;
	}
	
	for (auto Item : Items) {

		UWidget* TabItem = CreateWidget<UTabControl>(this, TabClass);
		if (!TabItem) {
			continue;
		}

		UTabControl* Tab = Cast<UTabControl>(TabItem);
		if (!Tab) {
			continue;
		}
		Tab->Id = Item.Key;
		Tab->Name = Item.Value;

		Tab->OnSelect.RemoveAll(this);
		Tab->OnSelect.AddDynamic(this, &UTabBoxControl::OnTabSelected);

		TabObjects.Add(Tab);

		HandleTab(Tab);

	}
}

void UTabBoxControl::ClearTabs_Implementation()
{
	for (UTabControl* Tab : TabObjects) {
		Tab->OnSelect.RemoveAll(this);
		Tab->RemoveFromParent();
	}
	HandleClear();
}

void UTabBoxControl::OnTabSelected_Implementation(UTabControl* Tab)
{
	if (!Tab) {
		LOG_ERROR(LogTemp, this, "Tab is null");
		return;
	}
	for (UTabControl* tab : TabObjects) {
		Tab->HandleSelected(tab == Tab);
	}
	OnTabChanged.Broadcast(Tab->Id);
}

void UTabBoxControl::HandleTab_Implementation(UTabControl* Tab) {}
void UTabBoxControl::HandleClear_Implementation() {}
