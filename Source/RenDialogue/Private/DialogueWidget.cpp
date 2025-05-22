// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "DialogueWidget.h"

// Engine Headers
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Overlay.h"

// Project Headers



void UDialogueWidget::StartDialogue()
{
	DialogueIndex = 0;

	if (ShowDialogue())
	{
		HandleDialogueStarted();
	}
}

bool UDialogueWidget::ShowDialogue()
{
	if (LoadedDialogue.IsValidIndex(DialogueIndex) && IsValid(ContentTextBlock))
	{
		ContentTextBlock->SetText(LoadedDialogue[DialogueIndex]->DialogueText);
		return true;
	}

	EndDialogue();
	return false;
}

void UDialogueWidget::NextDialogue()
{
	DialogueIndex++;
	ShowDialogue();
}

void UDialogueWidget::EndDialogue()
{
	DialogueIndex = 0;
	HandleDialogueEnded();
}



void UDialogueWidget::HandleDialogueStarted_Implementation()
{
	OnDialogueStarted.Broadcast();
}

void UDialogueWidget::HandleDialogueEnded_Implementation()
{
	OnDialogueEnded.Broadcast();
}



void UDialogueWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(NextButton))
	{
		NextButton->OnClicked.AddDynamic(this, &UDialogueWidget::NextDialogue);
	}

	if (IsValid(SkipButton))
	{
		SkipButton->OnClicked.AddDynamic(this, &UDialogueWidget::EndDialogue);
	}

	if (IsValid(SpeakerTextBlock))
	{
		SpeakerTextBlock->SetText(SpeakerName);
	}

	if (IsValid(DialogueTable))
	{
		DialogueTable->GetAllRows(TEXT("DialogueContext"), LoadedDialogue);
		StartDialogue();
	}

}

void UDialogueWidget::NativeDestruct()
{
	if (IsValid(NextButton))
	{
		NextButton->OnClicked.RemoveAll(this);
	}

	if (IsValid(SkipButton))
	{
		SkipButton->OnClicked.RemoveAll(this);
	}

	LoadedDialogue.Empty();

	Super::NativeDestruct();
}

