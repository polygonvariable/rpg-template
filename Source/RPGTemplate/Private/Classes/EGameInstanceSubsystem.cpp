#include "Classes/EGameInstanceSubsystem.h"


bool UEGameInstanceSubsystem::ShouldCreateSubsystem(UObject* object) const
{
	return bAllowCreation;
}

void UEGameInstanceSubsystem::PostInitialize_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("[%s]: PostInitialized"), *this->GetName());
}

void UEGameInstanceSubsystem::OnInitialized_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("[%s]: OnInitialized"), *this->GetName());
}

void UEGameInstanceSubsystem::OnDeinitialized_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("[%s]: OnDeinitialized"), *this->GetName());
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