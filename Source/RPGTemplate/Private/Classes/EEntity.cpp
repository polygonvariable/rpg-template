#include "Classes/EEntity.h"


AEEntity::AEEntity()
{
	if (UCapsuleComponent* Capsule = GetCapsuleComponent())
	{
		Capsule->SetCapsuleHalfHeight(90.0f);
		Capsule->SetCapsuleRadius(35.0f);
	}
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

