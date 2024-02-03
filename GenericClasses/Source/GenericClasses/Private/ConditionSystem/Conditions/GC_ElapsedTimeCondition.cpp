// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericClasses/Public/ConditionSystem/Conditions/GC_ElapsedTimeCondition.h"
#include "EventSystem/GC_EventBlueprintFunctionLibrary.h"
#include "EventSystem/GC_EventFactory.h"

bool UGC_ElapsedTimeCondition::RunConditionSentence()
{
	return elapsedTimePassed;
}

void UGC_ElapsedTimeCondition::OnWaitDelayFinish(UGC_Event* finishEvent)
{
	elapsedTimePassed = true;
}

void UGC_ElapsedTimeCondition::OnPooledObjectCreated(FDataTableRowHandle creationDataHandle)
{
	Super::OnPooledObjectCreated(creationDataHandle);

	float waitDelaySeconds = 0.f;

	FGC_ElapsedTimeConditionRow* conditionRow = GetRow<FGC_ElapsedTimeConditionRow>(creationDataHandle);
	if (conditionRow)
	{
		waitDelaySeconds = conditionRow->waitDelaySeconds;
	}

	waitEvent = GC_EventFactory::BuildWaitDelayEvent(waitDelaySeconds);
	waitEvent->GetOnTimeOutEventDelegate().AddUObject(this, &UGC_ElapsedTimeCondition::OnWaitDelayFinish);
}

void UGC_ElapsedTimeCondition::OnPooledObjectDestroyed()
{
	Super::OnPooledObjectDestroyed();

	UGC_EventRegister* eventRegister = UGC_SingletonRegister::GetInstance<UGC_EventRegister>();
	eventRegister->UnregisterEvent(waitEvent);

	waitEvent = nullptr;
	elapsedTimePassed = false;
}

