// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/RenGameInstanceSubsystem.h"

#include "Developer/GameMetadataSettings.h"
#include "RenShared/Public/Macro/LogMacro.h"


void URenGameInstanceSubsystem::PostInitialize_Implementation()
{
	LOG_INFO(this, LogTemp, "PostInitialize");
}

void URenGameInstanceSubsystem::OnInitialized_Implementation()
{
	LOG_INFO(this, LogTemp, "OnInitialized");
}

void URenGameInstanceSubsystem::OnDeinitialized_Implementation()
{
	LOG_INFO(this, LogTemp, "OnDeinitialized");
}

void URenGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	OnInitialized();
}

void URenGameInstanceSubsystem::Deinitialize()
{
	Super::Deinitialize();
	OnDeinitialized();
}

bool URenGameInstanceSubsystem::ShouldCreateSubsystem(UObject* Object) const
{
	if (!Object)
	{
		LOG_ERROR(this, LogTemp, "Object is null");
		return false;
	}

	const UGameMetadataSettings* GameMetadata = GetDefault<UGameMetadataSettings>();
	if (!GameMetadata)
	{
		LOG_ERROR(this, LogTemp, "GameMetadataSettings is null");
		return false;
	}

	for (const TSubclassOf<USubsystem>& SubsystemClass : GameMetadata->SubsystemClasses)
	{
		if (this->GetClass() == SubsystemClass)
		{
			return true;
		}
	}
	return false;
}

UWorld* URenGameInstanceSubsystem::GetWorld() const
{
	return nullptr;
}

