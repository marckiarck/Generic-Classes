// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ObjectPooler/GC_PooledObjectInterface.h"
#include "GC_EventSequence.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnEventSequenceFinish);

UCLASS()
class GENERICCLASSES_API UGC_EventSequenceDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, DisplayName = "Events Array")
		TArray<struct FGC_EventCreationData> eventCreationDataArray;
};

UCLASS()
class UGC_EventSequence : public UObject, public IGC_PooledObjectInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(Transient)
		TArray<struct FGC_EventCreationData> eventCreationDataArray;

	int currentEvent = 0;

	UPROPERTY(Transient)
		UObject* eventData = nullptr;

	FOnEventSequenceFinish onEventSequenceFinish;

public:
	void ConfigureEventSequence(UGC_EventSequenceDataAsset* sequenceData, UObject* aditionalEventData = nullptr);

	FOnEventSequenceFinish& GetOnEventSequenceFinsihDelegate();

private:
	void RegisterSequenceEvent();

	UFUNCTION()
		void OnSequenceEventFinish(UGC_Event* finishedEvent);

protected:
	void OnPooledObjectDestroyed() override;

};
