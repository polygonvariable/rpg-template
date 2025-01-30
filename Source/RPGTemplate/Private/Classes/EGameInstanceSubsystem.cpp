#include "Classes/EGameInstanceSubsystem.h"


bool UEGameInstanceSubsystem::ShouldCreateSubsystem(UObject* Object) const
{
	if (!Object)
	{
		LOG_ERROR(LogTemp, this, "Object not found");
		return false;
	}

	const UGameMetadataSettings* GameMetadata = GetDefault<UGameMetadataSettings>();
	if (!GameMetadata)
	{
		LOG_ERROR(LogTemp, this, "GameMetadataSettings not found");
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

void UEGameInstanceSubsystem::PostInitialize_Implementation()
{
	LOG_INFO(LogTemp, this, "PostInitialize");
}

void UEGameInstanceSubsystem::OnInitialized_Implementation()
{
	LOG_INFO(LogTemp, this, "OnInitialized");
}

void UEGameInstanceSubsystem::OnDeinitialized_Implementation()
{
	LOG_INFO(LogTemp, this, "OnDeinitialized");
}

UEGameInstanceSubsystem* UEGameInstanceSubsystem::GetSubsystem(TSubclassOf<UEGameInstanceSubsystem> SubsystemClass) const
{
	const UGameInstance* GameInstance = GetGameInstance();
	if (!GameInstance)
	{
		return nullptr;
	}

	UGameInstanceSubsystem* Subsystem = GameInstance->GetSubsystemBase(SubsystemClass);
	if (!Subsystem)
	{
		return nullptr;
	}

	return CastChecked<UEGameInstanceSubsystem>(Subsystem);
}

/*
* Since the Game Instance Subsystem doesnt interact with the world.
*/
UWorld* UEGameInstanceSubsystem::GetWorld() const
{
	return nullptr;
}

void UEGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	OnInitialized();
}

void UEGameInstanceSubsystem::Deinitialize()
{
	Super::Deinitialize();
	OnDeinitialized();
}