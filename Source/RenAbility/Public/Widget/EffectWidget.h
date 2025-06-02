// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"

#include "ActiveGameplayEffectHandle.h"
#include "AttributeSet.h"
#include "Blueprint/UserWidget.h"
#include "GameplayTagContainer.h"

// Project Headers

// Generated Headers
#include "EffectWidget.generated.h"

// Forward Declarations
class UTextBlock;
class UProgressBar;
class UPanelWidget;
class UAbilityComponent;



/**
 *
 */
UCLASS(Abstract)
class UEffectCollectionEntryWidget : public UUserWidget
{

	GENERATED_BODY()

public:

	UFUNCTION()
	void RegisterASC(UAbilitySystemComponent* TargetASC, const FGameplayEffectSpec& SpecApplied, const FActiveGameplayEffectHandle& ActiveHandle);

protected:

	FNumberFormattingOptions FormatOptions;

	FActiveGameplayEffectHandle CurrentActiveHandle;



	UPROPERTY(Meta = (BindWidgetOptional))
	TObjectPtr<UProgressBar> DurationProgressBar;

	UPROPERTY(Meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> DurationTextBlock;

	UPROPERTY(Meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> StackTextBlock;

	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<UAbilitySystemComponent> ASC;



	UFUNCTION(BlueprintNativeEvent)
	void HandleEffectStackChanged(FActiveGameplayEffectHandle EffectHandle, int32 NewStackCount, int32 PreviousStackCount);
	virtual void HandleEffectStackChanged_Implementation(FActiveGameplayEffectHandle EffectHandle, int32 NewStackCount, int32 PreviousStackCount);

	UFUNCTION(BlueprintNativeEvent)
	void HandleEffectRemoved(const FGameplayEffectRemovalInfo& EffectRemovalInfo);
	virtual void HandleEffectRemoved_Implementation(const FGameplayEffectRemovalInfo& EffectRemovalInfo);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void HandleEffectTimeChanged();
	virtual void HandleEffectTimeChanged_Implementation();

	UFUNCTION(BlueprintCallable)
	void GetEffectDurationAndRemainingTime(float& Duration, float& RemainingTime);

protected:

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

};



/**
 *
 */
UCLASS(Abstract)
class UEffectCollectionWidget : public UUserWidget
{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag CaptureEffectTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UEffectCollectionEntryWidget> EntryWidgetClass;

protected:

	UPROPERTY(Meta = (BindWidgetOptional))
	TObjectPtr<UPanelWidget> EffectStackPanel;

	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<UAbilitySystemComponent> ASC;



	UFUNCTION()
	void RegisterASC(AActor* Actor);

	UFUNCTION()
	void OnEffectAdded(UAbilitySystemComponent* Target, const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle);

	UFUNCTION()
	void OnEffectRemoved(const FActiveGameplayEffect& EffectRemoved);



	UFUNCTION(BlueprintNativeEvent)
	void HandleEffectAdded(const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle);
	virtual void HandleEffectAdded_Implementation(const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle);

	UFUNCTION(BlueprintNativeEvent)
	void HandleEffectRemoved(const FActiveGameplayEffect& EffectRemoved);
	virtual void HandleEffectRemoved_Implementation(const FActiveGameplayEffect& EffectRemoved);



	UFUNCTION()
	void CleanUpASC();

protected:

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

};


/**
 *
 */
UCLASS(Abstract)
class UEffectDurationTagWidget : public UUserWidget
{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag CaptureDurationTag;

protected:

	FGameplayTagContainer DurationTags;

	FNumberFormattingOptions FormatOptions;


	UPROPERTY(Meta = (BindWidgetOptional))
	TObjectPtr<UProgressBar> DurationProgressBar;

	UPROPERTY(Meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> DurationTextBlock;

	UPROPERTY(Meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> StackTextBlock;

	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<UAbilitySystemComponent> ASC;


	UFUNCTION()
	void RegisterActor(AActor* Actor);

	UFUNCTION()
	void OnTagCountChanged(const FGameplayTag GameplayTag, int32 NewCount);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void HandleEffectTimeChanged();
	virtual void HandleEffectTimeChanged_Implementation();

	UFUNCTION(BlueprintCallable)
	void GetEffectDurationAndRemainingTime(float& Duration, float& RemainingTime);

protected:

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

};

