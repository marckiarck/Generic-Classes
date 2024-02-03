// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ObjectPooler/GC_PooledObjectInterface.h"
#include "GC_AIController.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct GENERICCLASSES_API FGC_ControllerSpawnRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
};

USTRUCT(BlueprintType, Blueprintable)
struct GENERICCLASSES_API FGC_AIControllerSpawnRow : public FGC_ControllerSpawnRow
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere)
		UBehaviorTree* behaviorTree = nullptr;
};

UCLASS()
class GENERICCLASSES_API AGC_AIController : public AAIController, public IGC_PooledObjectInterface
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(Transient)
	UBehaviorTree* currentBehaviorTree = nullptr;

	void OnPooledObjectCreated(FDataTableRowHandle creationDataHandle) override;
	void OnPooledObjectDestroyed() override;

};
