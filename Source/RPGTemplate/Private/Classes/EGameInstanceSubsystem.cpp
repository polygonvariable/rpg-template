#include "Classes/EGameInstanceSubsystem.h"


bool UEGameInstanceSubsystem::ShouldCreateSubsystem(UObject* Object) const
{
	if (!Object) {
		LOG_ERROR(LogTemp, this, "Object not found");
		return false;
	}

	const USubsystemSettings* Settings = GetDefault<USubsystemSettings>();
	if (!Settings) {
		LOG_ERROR(LogTemp, this, "SubsystemSettings not found");
		return false;
	}

	for (const TSubclassOf<USubsystem>& SubsystemClass : Settings->SubsystemClasses) {
		if (this->GetClass() == SubsystemClass) {
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
	if (const UGameInstance* GameInstance = GetGameInstance())
	{

		UGameInstanceSubsystem* subsystem = GameInstance->GetSubsystemBase(SubsystemClass);
		if (!subsystem) {
			return nullptr;
		}

		return CastChecked<UEGameInstanceSubsystem>(subsystem);

	}
	return nullptr;
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