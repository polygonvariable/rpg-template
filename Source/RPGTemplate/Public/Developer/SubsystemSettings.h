#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "SubsystemSettings.generated.h"


UCLASS(Config = Game, defaultconfig, meta = (DisplayName = "Subsystem Settings"))
class RPGTEMPLATE_API USubsystemSettings : public UDeveloperSettings
{

	GENERATED_BODY()

public:

	USubsystemSettings();

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General")
	TSet<TSubclassOf<UGameInstanceSubsystem>> SubsystemClasses;

};
