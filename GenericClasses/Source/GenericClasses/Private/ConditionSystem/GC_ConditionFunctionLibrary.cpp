// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericClasses/Public/ConditionSystem/GC_ConditionFunctionLibrary.h"
#include "ConditionSystem/Conditions/GC_ConditionSentence.h"
#include "GenericClasses/Public/GenericClassesMinimals.h"
#include "ConditionSystem/GC_ConditionEvent.h"


void UGC_ConditionFunctionLibrary::CheckCondition(TSubclassOf<class UGC_ConditionSentence> conditionClass, const FOnConditionResult OnTrue, const FOnConditionResult OnFalse, UObject* aditionalData)
{
	UGC_ObjectPooler* objectPooler = UGC_SingletonRegister::GetInstance<UGC_ObjectPooler>();
	UGC_ConditionSentence* conditionSentence = objectPooler->NewUObjectTemplated<UGC_ConditionSentence>(conditionClass);

	GC_CHECK_AND_DO(conditionSentence == nullptr, TEXT("Invalid Condition Class"), { return; });

	conditionSentence->SetConditionData(aditionalData);

	if (conditionSentence->CheckCondition())
	{
		OnTrue.ExecuteIfBound();
	}
	else
	{
		OnFalse.ExecuteIfBound();
	}
}

void UGC_ConditionFunctionLibrary::WaitConditionSuccess(TSubclassOf<UGC_ConditionSentence> conditionClass, const FOnConditionResult OnSuccess, const FOnConditionResult OnTimeOut, float conditionCheckDuration, UObject* aditionalData)
{
	UGC_EventRegister* eventRegister = UGC_SingletonRegister::GetInstance<UGC_EventRegister>();

	FGC_EventCreationData creationData = FGC_EventCreationData();
	creationData.eventClass = UGC_ConditionEvent::StaticClass();
	creationData.eventDuration = conditionCheckDuration;

	UGC_ConditionEvent* conditionEvent = eventRegister->RegisterTemplatedEvent<UGC_ConditionEvent>(creationData);
	conditionEvent->CreateConditionSentence(conditionClass);
	conditionEvent->ProvideAditionalData(aditionalData);

	conditionEvent->GetOnConditionSentenceChecked().AddLambda([=](bool conditionResult) {
		if (conditionResult)
		{
			OnSuccess.ExecuteIfBound();
		}
		});

	conditionEvent->GetOnTimeOutEventDelegate().AddLambda([=](UGC_Event* timedOutEvent) { OnTimeOut.ExecuteIfBound();  });
}
