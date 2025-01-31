#pragma once

#include "CoreMinimal.h"
#include "StampChangeComponent.h"
#include "StampChangeCooldownComponent.generated.h"


UENUM(BlueprintType, DisplayName = "StampChangeCooldown Status")
enum EStampChangeCooldownStatus
{
	Pending UMETA(DisplayName = "Pending"),
	Completed UMETA(DisplayName = "Completed"),
	Once UMETA(DisplayName = "Once"),
	NotFound UMETA(DisplayName = "Not Found"),
};


UCLASS(DisplayName = "StampChangeCooldown Component")
class RPGTEMPLATE_API UStampChangeCooldownComponent : public UStampChangeComponent
{

	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StampChangeCooldown Component|Item")
	FTimespan CooldownTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StampChangeCooldown Component|Item")
	bool bOnlyOnce = false;

protected:

	virtual void ActivateStage_Implementation() override;

public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStampChangeCooldownStatus, EStampChangeCooldownStatus, Status);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "StampChangeCooldown Component|Event Dispatcher")
	FOnStampChangeCooldownStatus OnStampChangeCooldownStatus;
	
};
