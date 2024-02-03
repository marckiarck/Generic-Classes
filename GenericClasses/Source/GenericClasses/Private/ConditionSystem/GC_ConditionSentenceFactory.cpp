// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericClasses/Public/ConditionSystem/GC_ConditionSentenceFactory.h"
#include "GenericClasses/Public/GenericClassesMinimals.h"
#include "ConditionSystem/GC_ConditionEvent.h"


UGC_ConditionSentence* GC_ConditionSentenceFactory::BuildConditionSentence(TSubclassOf<UGC_ConditionSentence> conditionSentenceClass, FDataTableRowHandle conditionsSpawnHandle /*= FDataTableRowHandle()*/)
{
	UGC_ObjectPooler* objectPooler = UGC_SingletonRegister::GetInstance<UGC_ObjectPooler>();
	UGC_ConditionSentence* returnedConditionSentence = objectPooler->NewUObjectTemplated<UGC_ConditionSentence>(conditionSentenceClass, conditionsSpawnHandle);

	GC_CHECK(returnedConditionSentence == nullptr, TEXT("Builded condition sentence failed"));

	return returnedConditionSentence;
}

UGC_ConditionSentence* GC_ConditionSentenceFactory::BuildConditionSentenceWithData(const FGC_ConditionCreationData& conditionCreationData)
{
	return BuildConditionSentence(conditionCreationData.conditionSentenceClass, conditionCreationData.conditionsSpawnHandle);
}

UGC_ConditionEvent* GC_ConditionSentenceFactory::BuildConditionEvent(const FGC_ConditionCreationData& conditionCreationData)
{
	UGC_ConditionSentence* conditionSentence = GC_ConditionSentenceFactory::BuildConditionSentenceWithData(conditionCreationData);

	FGC_EventCreationData creationData = FGC_EventCreationData();
	creationData.eventClass = UGC_ConditionEvent::StaticClass();

	UGC_EventRegister* eventRegister = UGC_SingletonRegister::GetInstance<UGC_EventRegister>();
	UGC_ConditionEvent* returnedConditionEvent = eventRegister->RegisterTemplatedEvent<UGC_ConditionEvent>(creationData);

	if (conditionSentence)
	{
		returnedConditionEvent->SetConditionSentence(conditionSentence);
	}

	return returnedConditionEvent;
}
