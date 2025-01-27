#include "Classes/EEntity.h"


AEEntity::AEEntity()
{

	if (UCapsuleComponent* capsule = GetCapsuleComponent()) {
		capsule->SetCapsuleHalfHeight(90.0f);
		capsule->SetCapsuleRadius(35.0f);
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

