#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "EEntity.generated.h"


UCLASS(DisplayName = "Extended Entity")
class RPGTEMPLATE_API AEEntity : public ACharacter
{

	GENERATED_BODY()

public:

	AEEntity();

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
