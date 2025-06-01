// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"

// Project Headers


// Generated Headers
#include "AttributeWidget.generated.h"

// Forward Declarations
class UTextBlock;
class UProgressBar;
class UAbilitySystemComponent;
class UAbilityComponent;


/**
 *
 */
UCLASS(Abstract)
class UAttributeClampedWidget : public UUserWidget
{

	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Title;

	UPROPERTY(BlueprintReadOnly)
	float CurrentValue = 0.0f;

	UPROPERTY(BlueprintReadOnly)
	float CurrentMax = 0.0f;



	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttribute BaseAttribute;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttribute MaxAttribute;



	UPROPERTY(Meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> TitleTextBlock;

	UPROPERTY(Meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> ValueTextBlock;

	UPROPERTY(Meta = (BindWidgetOptional))
	TObjectPtr<UProgressBar> ValueProgressBar;


	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<UAbilityComponent> BaseASC;

	TArray<TWeakObjectPtr<UAbilityComponent>> AggregatedASC;


	UFUNCTION(BlueprintNativeEvent)
	void HandleValueChanged();
	virtual void HandleValueChanged_Implementation();

protected:

	UFUNCTION()
	void RegisterActor(AActor* Actor);

	UFUNCTION()
	void OnAggregatedRefresh();

protected:

	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

};



/**
 *
 */
UCLASS(Abstract)
class UAttributeScalarWidget : public UUserWidget
{

	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Title;

	UPROPERTY(BlueprintReadOnly)
	float CurrentValue = 0.0f;



	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttribute BaseAttribute;



	UPROPERTY(Meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> TitleTextBlock;

	UPROPERTY(Meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> ValueTextBlock;



	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<UAbilityComponent> BaseASC;



	UFUNCTION(BlueprintNativeEvent)
	void HandleValueChanged();
	virtual void HandleValueChanged_Implementation();

protected:

	UFUNCTION()
	void RegisterActor(AActor* Actor);

	UFUNCTION()
	void OnAggregatedRefresh();

protected:

	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

};

