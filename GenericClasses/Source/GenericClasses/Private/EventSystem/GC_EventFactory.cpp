// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericClasses/Public/EventSystem/GC_EventFactory.h"
#include "GenericClasses/Public/GenericClassesMinimals.h"

UGC_Event* GC_EventFactory::BuildWaitDelayEvent(float waitTime)
{
	UGC_EventRegister* eventRegister = UGC_SingletonRegister::GetInstance<UGC_EventRegister>();

	FGC_EventCreationData creationData = FGC_EventCreationData();
	creationData.eventClass = UGC_Event::StaticClass();
	creationData.eventDuration = waitTime;

	UGC_Event* waitEvent = eventRegister->RegisterEvent(creationData);

	return waitEvent;
}
