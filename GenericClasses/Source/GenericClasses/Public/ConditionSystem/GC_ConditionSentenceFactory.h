// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Conditions/GC_ConditionSentence.h"
#include "Engine/DataTable.h"
#include "GC_ConditionSentenceFactory.generated.h"


USTRUCT(BlueprintType, Blueprintable)
struct GENERICCLASSES_API FGC_ConditionCreationData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, DisplayName = "Condition Sentence")
	TSubclassOf<UGC_ConditionSentence> conditionSentenceClass;

	UPROPERTY(EditAnywhere, DisplayName = "Condition Creation Parameters")
	FDataTableRowHandle conditionsSpawnHandle;

};

class GENERICCLASSES_API GC_ConditionSentenceFactory
{
public:
	template<typename T>
	static T* BuildConditionSentence(FDataTableRowHandle conditionsSpawnHandle = FDataTableRowHandle());
	static UGC_ConditionSentence* BuildConditionSentence(TSubclassOf<UGC_ConditionSentence> conditionSentenceClass, FDataTableRowHandle conditionsSpawnHandle = FDataTableRowHandle());
	static UGC_ConditionSentence* BuildConditionSentenceWithData(const FGC_ConditionCreationData& conditionCreationData);

	static class UGC_ConditionEvent* BuildConditionEvent(const FGC_ConditionCreationData& conditionCreationData);
};

template<typename T>
T* GC_ConditionSentenceFactory::BuildConditionSentence(FDataTableRowHandle conditionsSpawnHandle)
{
	UGC_ConditionSentence*  returnedCondition = BuildConditionSentence(T::StaticClass(), conditionsSpawnHandle);
	return Cast<T>(returnedCondition);
}
