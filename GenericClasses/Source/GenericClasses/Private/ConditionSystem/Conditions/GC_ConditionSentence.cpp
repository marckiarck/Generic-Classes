// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericClasses/Public/ConditionSystem/Conditions/GC_ConditionSentence.h"
#include "SingletonRegister/GC_SingletonRegister.h"
#include "ObjectPooler/GC_ObjectPooler.h"

bool UGC_ConditionSentence::CheckCondition()
{
	bool conditionResult = RunConditionSentence();
	onConditionSentenceChecked.Broadcast(conditionResult);

	return conditionResult;
}

void UGC_ConditionSentence::SetConditionData(UObject* conditionDataContainer)
{

}

bool UGC_ConditionSentence::RunConditionSentence()
{
	return true;
}

void UGC_ConditionSentence::OnPooledObjectCreated(FDataTableRowHandle creationDataHandle)
{
	
}

void UGC_ConditionSentence::OnPooledObjectDestroyed()
{
	onConditionSentenceChecked.Clear();
}

FOnConditionSentenceChecked& UGC_ConditionSentence::GetOnConditionSentenceChecked()
{
	return onConditionSentenceChecked;
}
