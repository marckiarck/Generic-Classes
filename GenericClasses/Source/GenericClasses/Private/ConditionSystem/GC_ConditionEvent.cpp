// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericClasses/Public/ConditionSystem/GC_ConditionEvent.h"
#include "GenericClasses/Public/GenericClassesMinimals.h"
#include "DebugSystem/GC_DebugSystem.h"

void UGC_ConditionEvent::OnEventTick(float deltaSeconds)
{
	GC_CHECK_AND_DO(conditionSentence == nullptr, TEXT("Launched a ConditionEvent with a nullptr condition sentence"), {
		FinishEvent();
		return;
		})

	if (conditionSentence->CheckCondition())
	{
		FinishEvent();
	}
	
}

void UGC_ConditionEvent::CreateConditionSentence(TSubclassOf<UGC_ConditionSentence> conditionClass, FDataTableRowHandle creationDataHandle /*= FDataTableRowHandle ()*/)
{
	GC_CHECK(conditionSentence && conditionSentence->IsValidLowLevel(), FString::Printf(TEXT("Overriding previous Condition Sentence of %s"), *GetName()));

	UGC_ObjectPooler* objectPooler = UGC_SingletonRegister::GetInstance<UGC_ObjectPooler>();
	conditionSentence = objectPooler->NewUObjectTemplated<UGC_ConditionSentence>(conditionClass, creationDataHandle);
}

void UGC_ConditionEvent::CreateConditionSentenceWithData(FGC_ConditionCreationData conditionCreationData)
{
	CreateConditionSentence(conditionCreationData.conditionSentenceClass, conditionCreationData.conditionsSpawnHandle);
}

void UGC_ConditionEvent::SetConditionSentence(UGC_ConditionSentence* newConditionSentence)
{
	GC_CHECK(conditionSentence && conditionSentence->IsValidLowLevel(), FString::Printf(TEXT("Overriding previous Condition Sentence of %s"), *GetName()));
	if (newConditionSentence && conditionSentence)
	{
		UGC_ObjectPooler* objectPooler = UGC_SingletonRegister::GetInstance<UGC_ObjectPooler>();
		objectPooler->DestroyObject(newConditionSentence);
	}

	conditionSentence = newConditionSentence;
}

FOnConditionSentenceChecked& UGC_ConditionEvent::GetOnConditionSentenceChecked()
{
	return conditionSentence->GetOnConditionSentenceChecked();
}

void UGC_ConditionEvent::ProvideAditionalData(UObject* aditionalData)
{
	GC_CHECK_AND_DO(conditionSentence == nullptr, TEXT("Codition event is trying to provide aditional data to a nullptr Condition Sentence"), {
		return;
		});

	conditionSentence->SetConditionData(aditionalData);
}

const UGC_ConditionSentence* UGC_ConditionEvent::GetConditionSentence()
{
	return conditionSentence;
}

void UGC_ConditionEvent::OnPooledObjectCreated(FDataTableRowHandle creationDataHandle)
{
	Super::OnPooledObjectCreated(creationDataHandle);

	eventTickEnabled = true;
}

void UGC_ConditionEvent::OnPooledObjectDestroyed()
{
	Super::OnPooledObjectDestroyed();

	UGC_ObjectPooler* objectPooler = UGC_SingletonRegister::GetInstance<UGC_ObjectPooler>();
	objectPooler->DestroyObject(conditionSentence);

	conditionSentence = nullptr;
}
