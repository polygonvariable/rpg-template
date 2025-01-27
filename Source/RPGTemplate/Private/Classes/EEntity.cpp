#include "Classes/EEntity.h"


AEEntity::AEEntity()
{

	PrimaryActorTick.bCanEverTick = false;

}

void AEEntity::BeginPlay()
{

	Super::BeginPlay();
	
}

void AEEntity::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

}

void AEEntity::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

