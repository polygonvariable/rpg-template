// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/RenGameInstanceSubsystem.h"

#include "Developer/GameMetadataSettings.h"
#include "RenShared/Public/Macro/LogMacro.h"


void URenGameInstanceSubsystem::PostInitialize_Implementation()
{
	LOG_WARNING(this, LogTemp, "PostInitialize");
}

void URenGameInstanceSubsystem::OnInitialized_Implementation()
{
	LOG_WARNING(this, LogTemp, "OnInitialized");
}

void URenGameInstanceSubsystem::OnDeinitialized_Implementation()
{
	LOG_WARNING(this, LogTemp, "OnDeinitialized");
}

void URenGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Execute_OnInitialized(this);
}

void URenGameInstanceSubsystem::Deinitialize()
{
	Execute_OnDeinitialized(this);
	Super::Deinitialize();
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
	
	for (auto& SubsystemClass : GameMetadata->SubsystemClasses)
	{
		if (SubsystemClass == this->GetClass())
		{
			LOG_WARNING(this, LogTemp, "Subsystem found");
			return true;
		}
	}

	LOG_ERROR(this, LogTemp, "Subsystem not found");
	return false;
}

UWorld* URenGameInstanceSubsystem::GetWorld() const
{
	return nullptr;
}

