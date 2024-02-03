// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ConditionSystem/Conditions/GC_ConditionSentence.h"
#include "ObjectPooler/GC_PooledObjectInterface.h"
#include "GC_ElapsedTimeCondition.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct GENERICCLASSES_API FGC_ElapsedTimeConditionRow : public FGC_ConditionSentenceRow
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	float waitDelaySeconds = 0.f;
};

UCLASS()
class UGC_ElapsedTimeCondition : public UGC_ConditionSentence
{
	GENERATED_BODY()

private:
	bool elapsedTimePassed = false;

	UPROPERTY(Transient)
	UGC_Event* waitEvent;
	
protected:
	bool RunConditionSentence() override;

	UFUNCTION()
	void OnWaitDelayFinish(UGC_Event* finishEvent);

	void OnPooledObjectCreated(FDataTableRowHandle creationDataHandle) override;
	void OnPooledObjectDestroyed() override;

};
