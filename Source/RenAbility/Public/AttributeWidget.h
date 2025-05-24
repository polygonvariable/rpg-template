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
	float CurrentBase = 0.0f;

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
	TObjectPtr<UAbilitySystemComponent> AbilityComponent;



	UFUNCTION(BlueprintNativeEvent)
	void HandleValueChanged();
	virtual void HandleValueChanged_Implementation();



	void OnNewPawn(APawn* NewPawn);
	void OnBaseAttributeChanged(const FOnAttributeChangeData& Data);
	void OnMaxAttributeChanged(const FOnAttributeChangeData& Data);

protected:

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
	float CurrentBase = 0.0f;



	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttribute BaseAttribute;



	UPROPERTY(Meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> TitleTextBlock;

	UPROPERTY(Meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> ValueTextBlock;



	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAbilitySystemComponent> AbilityComponent;


	UFUNCTION(BlueprintNativeEvent)
	void HandleValueChanged();
	virtual void HandleValueChanged_Implementation();


	void OnNewPawn(APawn* NewPawn);
	void OnBaseAttributeChanged(const FOnAttributeChangeData& Data);

protected:

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

};

