#pragma once

#include "CoreMinimal.h"
#include "Classes/EActorComponent.h"
#include "StampChangeComponent.generated.h"

class UESaveGame;


UENUM(BlueprintType, DisplayName = "StampChange Status")
enum EStampChangeStatus
{
	Changed UMETA(DisplayName = "Changed"),
	Unchanged UMETA(DisplayName = "Unchanged"),
};


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), DisplayName="StampChange Component")
class RPGTEMPLATE_API UStampChangeComponent : public UEActorComponent
{

	GENERATED_BODY()

public:

	UPROPERTY(Interp, EditAnywhere, Category = "StampChange Component|Item")
	FGuid UUID;

	UPROPERTY(Interp, EditAnywhere, AdvancedDisplay, Category = "StampChange Component|Runtime")
	TObjectPtr<UESaveGame> Storage;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStampChangeStatus, EStampChangeStatus, Status);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "StampChange Component|Event Dispatcher")
	FOnStampChangeStatus OnStampChangeStatus;

protected:

	virtual void BeginStage_Implementation(FInstancedStruct Parameters) override;
	virtual bool ValidateStage_Implementation();
	virtual void ActivateStage_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "StampChange Component|Action")
	void AddChange(bool Force = false);
	virtual void AddChange_Implementation(bool Force = false);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "StampChange Component|Action")
	void RemoveChange();
	virtual void RemoveChange_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintPure), Category = "StampChange Component|Action")
	bool HasChanged();
	virtual bool HasChanged_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "StampChange Component|Action")
	bool GetChangedDate(FDateTime& ChangedDate);
	virtual bool GetChangedDate_Implementation(FDateTime& ChangedDate);
	
};
