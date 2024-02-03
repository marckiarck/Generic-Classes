// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ObjectPooler/GC_ObjectPooler.h"
#include "GC_Event.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnEventStarts, UGC_Event*);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnEventFinish, UGC_Event*);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnEventTick, UGC_Event*, float);


UCLASS(BlueprintType)
class GENERICCLASSES_API UGC_Event : public UObject, public IGC_PooledObjectInterface
{
	GENERATED_BODY()

public:

	virtual void ProvideAditionalData(UObject* aditionalData);
	void SetEventDuration(float newEventDuration);
	void LaunchEvent(float deltaSeconds);

	UFUNCTION(BlueprintCallable)
		void FinishEvent();

	FOnEventStarts& GetOnStartEventDelegate();
	FOnEventTick& GetOnEventTickDelegate();
	FOnEventFinish& GetOnFinishEventDelegate();
	FOnEventFinish& GetOnTimeOutEventDelegate();

	bool GetEventTickEnabled();

protected:

	UPROPERTY(EditDefaultsOnly)
		bool eventTickEnabled = true;

	void OnPooledObjectCreated(FDataTableRowHandle creationDataHandle) override;
	void OnPooledObjectDestroyed() override;

	virtual void OnEventStarted();
	virtual void OnEventTick(float deltaSeconds);
	virtual void OnEventFinish();
	virtual void OnEventTimeOut();

private:

	bool eventLaunched = false;
	bool eventFinished = false;

	float eventDuration = -1.f;
	float eventLifeTime = 0.f;

	FOnEventStarts OnStartEventDelegate;
	FOnEventTick OnEventTickDelegate;
	FOnEventFinish OnFinishEventDelegate;
	FOnEventFinish OnTimeOutEventDelegate;

	void StartEvent();
	void EventTick(float deltaSeconds);
};
