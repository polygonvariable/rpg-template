#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ControlWidget.generated.h"


UCLASS(Abstract, DisplayName = "Tab Control")
class RPGTEMPLATE_API UTabControl : public UUserWidget
{

	GENERATED_BODY()

public:

	UPROPERTY(Interp, EditAnywhere, Category = "Tab Control|Context")
	FName Id;

	UPROPERTY(Interp, EditAnywhere, Category = "Tab Control|Context")
	FText Name;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Tab Control|Action")
	void HandleSelected(bool bSelected = false);
	virtual void HandleSelected_Implementation(bool bSelected = false);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelect, UTabControl*, Tab);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Tab Control|Event Dispatcher")
	FOnSelect OnSelect;

protected:

	UPROPERTY(Interp, EditAnywhere, Category = "Tab Control|Context")
	bool bIsSelected = false;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Tab Control|Action")
	void Select();
	virtual void Select_Implementation();

};


UCLASS(Abstract, DisplayName = "TabBox Control")
class RPGTEMPLATE_API UTabBoxControl : public UUserWidget
{

	GENERATED_BODY()

public:

	UTabBoxControl(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "TabBox Control|Action")
	void BuildTabs(const TMap<FName, FText>& Items);
	virtual void BuildTabs_Implementation(const TMap<FName, FText>& Items);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "TabBox Control|Action")
	void ClearTabs();
	virtual void ClearTabs_Implementation();

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTabChanged, FName, Id);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "TabBox Control|Event Dispatcher")
	FOnTabChanged OnTabChanged;

protected:

	UPROPERTY(Interp, EditAnywhere, BlueprintReadOnly, Category = "TabBox Control|Item")
	TSubclassOf<UTabControl> TabClass = UTabControl::StaticClass();

	UPROPERTY(Interp, EditAnywhere, BlueprintReadOnly, Category = "TabBox Control|Item|Runtime")
	TSet<TObjectPtr<UTabControl>> TabObjects;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "TabBox Control|Action")
	void OnTabSelected(UTabControl* Tab);
	virtual void OnTabSelected_Implementation(UTabControl* Tab);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "TabBox Control|Handler")
	void HandleTab(UTabControl* Tab);
	virtual void HandleTab_Implementation(UTabControl* Tab);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "TabBox Control|Handler")
	void HandleClear();
	virtual void HandleClear_Implementation();

};