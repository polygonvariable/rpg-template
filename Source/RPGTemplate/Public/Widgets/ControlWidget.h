#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/PanelWidget.h"
#include "ControlWidget.generated.h"


UCLASS(Abstract, DisplayName = "Tab Control")
class RPGTEMPLATE_API UTabControl : public UUserWidget
{

	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, Category = "Tab Control|Runtime")
	FText Title;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Tab Control|Handler")
	void HandleSelected(bool bWasSelected = false);
	virtual void HandleSelected_Implementation(bool bWasSelected = false);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (BindWidgetOptional), Category = "Tab Control|Binding")
	TObjectPtr<UButton> TabButton;

	UPROPERTY(BlueprintReadWrite, Category = "Tab Control|Runtime")
	bool bIsSelected = false;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Tab Control|Action")
	void Select();
	virtual void Select_Implementation();

protected:

	virtual void NativeConstruct() override;

public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelect, UTabControl*, Tab);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Tab Control|Event Dispatcher")
	FOnSelect OnSelect;

};


UCLASS(Abstract, DisplayName = "TabBox Control")
class RPGTEMPLATE_API UTabBoxControl : public UUserWidget
{

	GENERATED_BODY()

public:

	UTabBoxControl(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (BindWidgetOptional), Category = "TabBox Control|Binding")
	TObjectPtr<UPanelWidget> TabContainer;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "TabBox Control|Action")
	void BuildTabs(const TSet<FName>& Items);
	virtual void BuildTabs_Implementation(const TSet<FName>& Items);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "TabBox Control|Action")
	void ClearTabs();
	virtual void ClearTabs_Implementation();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TabBox Control|Item")
	TSubclassOf<UTabControl> TabClass = UTabControl::StaticClass();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "TabBox Control|Action")
	void OnTabSelected(UTabControl* Tab);
	virtual void OnTabSelected_Implementation(UTabControl* Tab);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "TabBox Control|Handler")
	void HandleTab(UTabControl* Tab);
	virtual void HandleTab_Implementation(UTabControl* Tab);

public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTabChanged, FName, Title);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "TabBox Control|Event Dispatcher")
	FOnTabChanged OnTabChanged;

};
