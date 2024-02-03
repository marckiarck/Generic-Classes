// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericClasses/Public/EventSystem/GC_EventRegister.h"
#include "SingletonRegister/GC_SingletonRegister.h"
#include "ObjectPooler/GC_ObjectPooler.h"
#include "EventSystem/GC_EventSequence.h"
#include "DebugSystem/GC_DebugSystem.h"


UGC_Event* UGC_EventRegister::RegisterEvent(FGC_EventCreationData eventCreationData, UObject* aditionalData)
{
	UGC_ObjectPooler* objectPooler = UGC_SingletonRegister::GetInstance<UGC_ObjectPooler>();
	UGC_Event* registeredEvent = objectPooler->NewUObject<UGC_Event>(eventCreationData.eventClass, eventCreationData.eventSpawnHandle);
	registeredEvent->SetEventDuration(eventCreationData.eventDuration);
	if (aditionalData)
	{
		registeredEvent->ProvideAditionalData(aditionalData);
	}

	eventQueue.Enqueue(registeredEvent, eventCreationData.launchDelay);

	//[TODO] this debug should be inside the timed queue class
	TArray<UGC_Event*> testArray;
	eventQueue.GetQueueArray(testArray);
	GC_CHECK(testArray.Contains(registeredEvent) == false, TEXT("Registered event could not be added to the event queue"));

	return registeredEvent;
}

bool UGC_EventRegister::RegisterEvent(UGC_Event* eventReference)
{

	if (eventReference == nullptr)
	{
		UGC_DebugSystem* debugSystem = UGC_SingletonRegister::GetInstance<UGC_DebugSystem>();
		debugSystem->SendLog(TEXT("Trying to register nullptr event"));
		return false;
	}

	TArray<UGC_Event*> queuedEvents;
	eventQueue.GetQueueArray(queuedEvents);

	if (queuedEvents.Contains(eventReference) || launchedEvents.Contains(eventReference))
	{
		UGC_DebugSystem* debugSystem = UGC_SingletonRegister::GetInstance<UGC_DebugSystem>();
		debugSystem->SendLog(FString::Printf(TEXT("Trying to register %s. This event is already registered"), *eventReference->GetName()));
	}

	eventQueue.Enqueue(eventReference);

	return true;
}

UGC_EventSequence* UGC_EventRegister::RegisterEventSequence(UGC_EventSequenceDataAsset* sequenceData, UObject* aditionalData)
{
	if (sequenceData == nullptr)
	{
		ensureMsgf(sequenceData == nullptr, TEXT("Your are trying to register a event sequence with a null sequenceData"));
		return nullptr;
	}

	UGC_ObjectPooler* objectPooler = UGC_SingletonRegister::GetInstance<UGC_ObjectPooler>();
	UGC_EventSequence* eventSequence = objectPooler->NewUObject<UGC_EventSequence>();
	eventSequence->ConfigureEventSequence(sequenceData, aditionalData);

	return eventSequence;
}

void UGC_EventRegister::UnregisterEvent(UGC_Event* unregisteredEvent)
{
	//[TODO] here is where should be canceled events launched by a parent event
	if (unregisteredEvent == nullptr)
	{
		UGC_DebugSystem* debugSystem = UGC_SingletonRegister::GetInstance<UGC_DebugSystem>();
		debugSystem->SendLog(TEXT("Trying to unregister a nullptr event"));
	}

	TArray<UGC_Event*> queuedEvents;
	eventQueue.GetQueueArray(queuedEvents);
	if (queuedEvents.Contains(unregisteredEvent))
	{
		UGC_DebugSystem* debugSystem = UGC_SingletonRegister::GetInstance<UGC_DebugSystem>();
		debugSystem->SendLog(FString::Printf(TEXT("Trying to unregister queued event: %s"), *unregisteredEvent->GetName()));
	}

	unregisteredEvent->FinishEvent();
}

TArray<const UGC_Event*> UGC_EventRegister::GetLaunchedEvents()
{
	TArray<const UGC_Event*> returnedArray;
	for (const UGC_Event* launchedEvent : launchedEvents)
	{
		returnedArray.Add(launchedEvent);
	}

	return returnedArray;
}

TArray<const UGC_Event*> UGC_EventRegister::GetQueuedEvents()
{
	TArray<const UGC_Event*> returnedArray;
	TArray<UGC_Event*> queuedEvents;
	eventQueue.GetQueueArray(queuedEvents);
	for (const UGC_Event* queuedEvent : queuedEvents)
	{
		returnedArray.Add(queuedEvent);
	}

	return returnedArray;
}

void UGC_EventRegister::OnInstanceCreated_Implementation(FDataTableRowHandle singletonDataHandle)
{
	if (const UDataTable* eventDatatable = singletonDataHandle.DataTable)
	{
		FString contextString = TEXT("Event Register Creation");
		if (const FGC_EventRegisterDataRow* eventRegisterRow = eventDatatable->FindRow<FGC_EventRegisterDataRow>(singletonDataHandle.RowName, contextString))
		{
			queueDeltaTime = FMath::Max(0.f, eventRegisterRow->queueDeltaTime);
		}
	}

	InitializeEventRegister();

	if (GEngine)
	{
		OnWorldAddedDelegateHandle = GEngine->OnWorldAdded().AddUFunction(this, FName("OnWorldAdded"));
		OnWorldDestroyedDelegateHandle = GEngine->OnWorldDestroyed().AddUFunction(this, FName("OnWorldDestroyed"));
	}
}

void UGC_EventRegister::OnResetInstance_Implementation(FDataTableRowHandle singletonDataHandle)
{
	ShutDownEventRegister();

	if (GEngine)
	{
		GEngine->OnWorldAdded().Remove(OnWorldAddedDelegateHandle);
		GEngine->OnWorldDestroyed().Remove(OnWorldDestroyedDelegateHandle);
	}

	Execute_OnInstanceCreated(this, singletonDataHandle);
}

void UGC_EventRegister::UpdateEventQueue()
{
	TArray<UGC_Event*> poppedEvents;
	eventQueue.Dequeue(queueDeltaTime, poppedEvents);

	TArray<UGC_Event*> oneLauchEvents;
	//This for should be a  eventQueueDelegate??
	for (UGC_Event* poppedEventIt : poppedEvents)
	{
		poppedEventIt->GetOnFinishEventDelegate().AddUObject(this, &UGC_EventRegister::OnEventFinish);
		if (poppedEventIt->GetEventTickEnabled() == true)
		{
			launchedEvents.Add(poppedEventIt);
		}
		else
		{
			oneLauchEvents.Add(poppedEventIt);
		}
	}

	TArray<UGC_Event*> launchedEventsCpy = launchedEvents;
	launchedEventsCpy.Append(oneLauchEvents);
	for (UGC_Event* eventIt : launchedEventsCpy)
	{
		eventIt->LaunchEvent(queueDeltaTime);
	}

	TArray<UGC_Event*> finishedEventsCpy = finishedEvents;
	for (UGC_Event* finishedEventIt : finishedEventsCpy)
	{
		UGC_ObjectPooler* objectPooler = UGC_SingletonRegister::GetInstance<UGC_ObjectPooler>();
		objectPooler->DestroyUObject<UGC_Event>(finishedEventIt);

		finishedEvents.Remove(finishedEventIt);
	}
}

void UGC_EventRegister::InitializeEventRegister()
{
	timerWorld = GEngine->GetCurrentPlayWorld();
	if (timerWorld)
	{
		timerWorld->GetTimerManager().ClearTimer(queueTimerHandle);
		timerWorld->GetTimerManager().SetTimer(queueTimerHandle, this, &UGC_EventRegister::UpdateEventQueue, queueDeltaTime, true);
	}

	eventQueue = TGC_EventQueue<UGC_Event>();
}

void UGC_EventRegister::ShutDownEventRegister()
{
	if (timerWorld)
	{
		timerWorld->GetTimerManager().ClearTimer(queueTimerHandle);
		timerWorld = nullptr;
	}

	TArray<UGC_Event*> launchedEventsCpy = launchedEvents;
	for (UGC_Event* launchedEventIt : launchedEventsCpy)
	{
		UnregisterEvent(launchedEventIt);
	}
	launchedEvents.Empty();

	for (UGC_Event* finishedEvent : finishedEvents) 
	{
		UGC_ObjectPooler* objectPooler = UGC_SingletonRegister::GetInstance<UGC_ObjectPooler>();
		objectPooler->DestroyUObject<UGC_Event>(finishedEvent);
	}
	finishedEvents.Empty();

	TArray<UGC_Event*> queuedEvents;
	eventQueue.GetQueueArray(queuedEvents);
	UGC_ObjectPooler* objectPooler = UGC_SingletonRegister::GetInstance<UGC_ObjectPooler>();
	for (UGC_Event* queuedEventIt : queuedEvents)
	{
		objectPooler->DestroyUObject<UGC_Event>(queuedEventIt);
	}
}

void UGC_EventRegister::OnWorldDestroyed(UWorld* destroyedWorld)
{
	/*
	* Maybe this is not the ideal way to ShotDown the event register ??
	* Should separate timer set up from launched events??
	*/
	if (destroyedWorld == timerWorld)
	{
		ShutDownEventRegister();
	}
}

void UGC_EventRegister::OnWorldAdded(UWorld* addedWorld)
{
	if (timerWorld == nullptr)
	{
		InitializeEventRegister();
	}
}

void UGC_EventRegister::BindToEventsOnFinish(TArray<UGC_Event*> eventsArray)
{
	for (UGC_Event* eventIt : eventsArray)
	{
		eventIt->GetOnFinishEventDelegate().AddUObject(this, &UGC_EventRegister::OnEventFinish);
	}
}

void UGC_EventRegister::OnEventFinish(UGC_Event* finishedEvent)
{
	launchedEvents.Remove(finishedEvent);
	finishedEvents.Add(finishedEvent);
}
