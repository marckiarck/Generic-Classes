// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GC_Character.h"
#include "ConditionSystem/Conditions/GC_ConditionSentence.h"
#include "EventSystem/GC_EventRegister.h"
#include "ConditionSystem/GC_ConditionSentenceFactory.h"
#include "GC_CharacterSpawner.generated.h"

UCLASS()
class AGC_CharacterSpawner : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = CharacterSpawner)
		TSubclassOf<AGC_Character> characterClass;

	UPROPERTY(EditAnywhere, Category = CharacterSpawner, meta = (RowType = "GC_CharacterSpawnRow"))
		FDataTableRowHandle spawnDataRowHandle;

	UPROPERTY(Transient)
		AGC_Character* spawnedCharacter;

	UPROPERTY(EditAnywhere, Category="SpawnCondition", meta = (RowType = "GC_ConditionSentenceRow"))
	FGC_ConditionCreationData conditionCreationData;

	UPROPERTY(EditAnywhere, Category="SpawnEvent")
	FGC_EventCreationData spawnEventCreationData;
	
public:	
	// Sets default values for this actor's properties
	AGC_CharacterSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void SpawnCharacter();

	UFUNCTION()
	void OnSpawnConditionSuccess(UGC_Event* successConditionEvent);
};
