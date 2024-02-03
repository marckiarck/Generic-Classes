// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericClasses/Public/EventSystem/Events/GC_Event.h"
#include "SingletonRegister/GC_SingletonRegister.h"
#include "EventSystem/GC_EventRegister.h"

void UGC_Event::StartEvent()
{
	eventLaunched = true;
	OnEventStarted();
	OnStartEventDelegate.Broadcast(this);
	eventFinished = false;
}

void UGC_Event::FinishEvent()
{
	if (eventFinished == false)
	{
		eventFinished = true;
		OnEventFinish();
		OnFinishEventDelegate.Broadcast(this);
	}
}

void UGC_Event::EventTick(float deltaSeconds)
{
	OnEventTick(deltaSeconds);
	OnEventTickDelegate.Broadcast(this, deltaSeconds);
}

void UGC_Event::ProvideAditionalData(UObject* aditionalData)
{

}

void UGC_Event::SetEventDuration(float newEventDuration)
{
	eventDuration = newEventDuration;
}

void UGC_Event::LaunchEvent(float deltaSeconds)
{
	if (eventLaunched == false)
	{
		StartEvent();
	}

	if (eventTickEnabled)
	{
		EventTick(deltaSeconds);

		eventLifeTime += deltaSeconds;
		if (eventDuration >= 0.f && eventLifeTime >= eventDuration)
		{
			OnTimeOutEventDelegate.Broadcast(this);
			FinishEvent();
		}
	}

}

FOnEventStarts& UGC_Event::GetOnStartEventDelegate()
{
	return OnStartEventDelegate;
}

FOnEventFinish& UGC_Event::GetOnFinishEventDelegate()
{
	return OnFinishEventDelegate;
}

FOnEventFinish& UGC_Event::GetOnTimeOutEventDelegate()
{
	return OnTimeOutEventDelegate;
}

FOnEventTick& UGC_Event::GetOnEventTickDelegate()
{
	return OnEventTickDelegate;
}

bool UGC_Event::GetEventTickEnabled()
{
	return eventTickEnabled;
}

void UGC_Event::OnPooledObjectCreated(FDataTableRowHandle creationDataHandle)
{

}

void UGC_Event::OnPooledObjectDestroyed()
{
	OnStartEventDelegate.Clear();
	OnFinishEventDelegate.Clear();
	OnEventTickDelegate.Clear();
	OnTimeOutEventDelegate.Clear();

	eventLaunched = false;
	eventFinished = false;

	eventLifeTime = 0.f;
}

void UGC_Event::OnEventStarted()
{
}

void UGC_Event::OnEventTick(float deltaSeconds)
{
}

void UGC_Event::OnEventFinish()
{
}

void UGC_Event::OnEventTimeOut()
{
}

