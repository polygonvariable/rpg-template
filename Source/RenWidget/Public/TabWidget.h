// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

// Generated Headers
#include "TabWidget.generated.h"

// Forward Declarations
class UButton;
class UTextBlock;
class UPanelWidget;


/**
 *
 */
UCLASS(Abstract, DisplayName = "Tab Control")
class RENWIDGET_API UTabControl : public UUserWidget
{

	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, Category = "Tab Control|Runtime")
	FText Title;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Tab Control|Action")
	void Select(bool bSelected = false);
	virtual void Select_Implementation(bool bSelected = false);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (BindWidgetOptional), Category = "Tab Control|Binding")
	TObjectPtr<UButton> TabButton;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (BindWidgetOptional), Category = "Tab Control|Binding")
	TObjectPtr<UTextBlock> TabText;


	UPROPERTY(BlueprintReadWrite, Category = "Tab Control|Runtime")
	bool bIsSelected = false;


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Tab Control|Handler")
	void HandleSelection();
	virtual void HandleSelection_Implementation();

protected:

	virtual void NativeConstruct() override;

public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelect, UTabControl*, Tab);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Tab Control|Event Dispatcher")
	FOnSelect OnSelect;

};


/**
 *
 */
UCLASS(Abstract, DisplayName = "TabBox Control")
class RENWIDGET_API UTabBoxControl : public UUserWidget
{

	GENERATED_BODY()

public:

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