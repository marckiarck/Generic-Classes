// Fill out your copyright notice in the Description page of Project Settings.


#include "EventSystem/GC_EventBlueprintFunctionLibrary.h"
#include "SingletonRegister/GC_SingletonRegister.h"
#include "EventSystem/GC_EventSequence.h"
#include "DataStructures/Datatable/GC_DataTable.h"
#include "EventSystem/Events/GC_Event.h"


void UGC_EventBlueprintFunctionLibrary::RegisterEvent(FGC_EventCreationData eventCreationData, const FOnFinish onEventFinish, UObject* aditionalData)
{
	UGC_EventRegister* eventRegister = UGC_SingletonRegister::GetInstance<UGC_EventRegister>();

	UGC_Event* registeredEvent = eventRegister->RegisterEvent(eventCreationData, aditionalData);
	registeredEvent->GetOnFinishEventDelegate().AddLambda([=](UGC_Event* finishedEvent) {onEventFinish.ExecuteIfBound(); });
}

void UGC_EventBlueprintFunctionLibrary::RegisterEventSequence(class UGC_EventSequenceDataAsset* sequenceData, const FOnFinish onEventSequenceFinish, UObject* aditionalData)
{
	UGC_EventRegister* eventRegister = UGC_SingletonRegister::GetInstance<UGC_EventRegister>();

	UGC_EventSequence* registeredEventSequence = eventRegister->RegisterEventSequence(sequenceData, aditionalData);
	registeredEventSequence->GetOnEventSequenceFinsihDelegate().AddLambda([=]() {onEventSequenceFinish.ExecuteIfBound(); });
}

void UGC_EventBlueprintFunctionLibrary::WaitDelay(float waitTime, const FOnFinish onFinish)
{
	UGC_EventRegister* eventRegister = UGC_SingletonRegister::GetInstance<UGC_EventRegister>();

	FGC_EventCreationData creationData = FGC_EventCreationData();
	creationData.eventClass = UGC_Event::StaticClass();
	creationData.eventDuration = waitTime;

	UGC_Event* waitEvent = eventRegister->RegisterEvent(creationData);

	waitEvent->GetOnTimeOutEventDelegate().AddLambda([=](UGC_Event* timedOutEvent) { onFinish.ExecuteIfBound(); });
}

void UGC_EventBlueprintFunctionLibrary::DelegateTickEvent(const FOnFinish onFinish, const FOnStartEvent onStart, FOnTickEvent onEventTick, float launchDelay /*= 0.f*/, float eventDuration /*= -1.f*/)
{
	UGC_EventRegister* eventRegister = UGC_SingletonRegister::GetInstance<UGC_EventRegister>();

	FGC_EventCreationData creationData = FGC_EventCreationData();
	creationData.eventClass = UGC_Event::StaticClass();
	creationData.launchDelay = launchDelay;
	creationData.eventDuration = eventDuration;

	UGC_Event* delegateTickEvent = eventRegister->RegisterEvent(creationData);

	delegateTickEvent->GetOnStartEventDelegate().AddLambda([=](UGC_Event* startedEvent) {onStart.ExecuteIfBound(startedEvent); });
	delegateTickEvent->GetOnEventTickDelegate().AddLambda([=](UGC_Event* tickedEvent, float deltaSeconds) {onEventTick.ExecuteIfBound(tickedEvent, deltaSeconds); });
	delegateTickEvent->GetOnFinishEventDelegate().AddLambda([=](UGC_Event* finishedEvent) {onFinish.ExecuteIfBound(); });
}

void UGC_EventBlueprintFunctionLibrary::TestFunction(float value, int num, float& outValue, const FOnTest onTest, FGC_DataTableRowHandle rowHandle)
{
	outValue = value;
	GEngine->AddOnScreenDebugMessage(-1, 1000000.f, FColor::Yellow, FString::Printf(TEXT("%f\n%d"), value, num));
	onTest.ExecuteIfBound(TEXT("onTestString"));
}

