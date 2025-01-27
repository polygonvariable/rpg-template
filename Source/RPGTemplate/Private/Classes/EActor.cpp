#include "Classes/EActor.h"


AEActor::AEActor()
{

	PrimaryActorTick.bCanEverTick = false;

}

void AEActor::BeginPlay()
{

	Super::BeginPlay();
	
}

void AEActor::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

}

