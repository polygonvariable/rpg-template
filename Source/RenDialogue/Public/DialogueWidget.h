// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

// Project Headers
#include "RenDialogue/Public/DialogueData.h"

// Generated Headers
#include "DialogueWidget.generated.h"

// Forward Declarations
class UTextBlock;
class UButton;
class UOverlay;



/**
 *
 */
UCLASS(Abstract)
class UDialogueWidget : public UUserWidget
{

	GENERATED_BODY()

protected:

	TArray<FDialogueData*> LoadedDialogue;



	UPROPERTY(Meta = (BindWidgetOptional))
	TObjectPtr<UOverlay> DialogueContainer;

	UPROPERTY(Meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> SpeakerTextBlock;

	UPROPERTY(Meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> ContentTextBlock;

	UPROPERTY(Meta = (BindWidgetOptional))
	TObjectPtr<UButton> NextButton;

	UPROPERTY(Meta = (BindWidgetOptional))
	TObjectPtr<UButton> SkipButton;



	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UDataTable> DialogueTable;



	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText SpeakerName;

	UPROPERTY(BlueprintReadOnly)
	int DialogueIndex = 0;
	


	UFUNCTION(BlueprintCallable)
	void StartDialogue();

	UFUNCTION(BlueprintCallable)
	bool ShowDialogue();

	UFUNCTION(BlueprintCallable)
	void NextDialogue();

	UFUNCTION(BlueprintCallable)
	void EndDialogue();



	UFUNCTION(BlueprintImplementableEvent)
	void HandleDialogueStarted();
	virtual void HandleDialogueStarted_Implementation();

	UFUNCTION(BlueprintImplementableEvent)
	void HandleDialogueEnded();
	virtual void HandleDialogueEnded_Implementation();

protected:

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogueStarted);
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnDialogueStarted OnDialogueStarted;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogueEnded);
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnDialogueEnded OnDialogueEnded;

};

