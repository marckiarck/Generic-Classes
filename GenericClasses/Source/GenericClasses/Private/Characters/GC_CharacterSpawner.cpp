// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/GC_CharacterSpawner.h"
#include "GenericClasses/Public/GenericClassesMinimals.h"
#include "ConditionSystem/GC_ConditionEvent.h"

// Sets default values
AGC_CharacterSpawner::AGC_CharacterSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AGC_CharacterSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	if (conditionCreationData.conditionSentenceClass->IsValidLowLevel())
	{
		UGC_EventRegister* eventRegister = UGC_SingletonRegister::GetInstance<UGC_EventRegister>();

		FGC_EventCreationData creationData = FGC_EventCreationData();
		creationData.eventClass = UGC_ConditionEvent::StaticClass();

		UGC_ConditionEvent* conditionEvent = eventRegister->RegisterTemplatedEvent<UGC_ConditionEvent>(creationData);
		conditionEvent->CreateConditionSentenceWithData(conditionCreationData);
		conditionEvent->GetOnFinishEventDelegate().AddUObject(this, &AGC_CharacterSpawner::OnSpawnConditionSuccess);
	}
	else
	{
		SpawnCharacter();
	}
	
}

void AGC_CharacterSpawner::SpawnCharacter()
{
	FString ContextString = TEXT("Character Spawner context");

	if (const UDataTable* spawnDatatable = spawnDataRowHandle.DataTable)
	{
		if (const FGC_CharacterSpawnRow* spawnRow = spawnDatatable->FindRow<FGC_CharacterSpawnRow>(spawnDataRowHandle.RowName, ContextString))
		{
			TSubclassOf<AActor> spawnClass = characterClass;
			if (UGC_ObjectPooler* objectPooler = UGC_SingletonRegister::GetInstance<UGC_ObjectPooler>())
			{
				spawnedCharacter = objectPooler->SpawnActor<AGC_Character>(GetLevel(), spawnClass, GetActorTransform(), spawnDataRowHandle);
			}
		}
	}
}

void AGC_CharacterSpawner::OnSpawnConditionSuccess(UGC_Event* successConditionEvent)
{
	SpawnCharacter();

	if (spawnEventCreationData.eventClass->IsValidLowLevel())
	{
		UGC_EventRegister* eventRegister = UGC_SingletonRegister::GetInstance<UGC_EventRegister>();
		
		eventRegister->RegisterEvent(spawnEventCreationData);
	}
	
}

