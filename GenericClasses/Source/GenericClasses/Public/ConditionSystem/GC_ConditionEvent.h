// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EventSystem/Events/GC_Event.h"
#include "Conditions/GC_ConditionSentence.h"
#include "GC_ConditionSentenceFactory.h"
#include "GC_ConditionEvent.generated.h"



UCLASS()
class GENERICCLASSES_API UGC_ConditionEvent : public UGC_Event
{
	GENERATED_BODY()
	
private:
	UGC_ConditionSentence* conditionSentence;

public:
	virtual void OnEventTick(float deltaSeconds) override;

	void CreateConditionSentence(TSubclassOf<UGC_ConditionSentence> conditionClass, FDataTableRowHandle creationDataHandle =  FDataTableRowHandle ());
	void CreateConditionSentenceWithData(FGC_ConditionCreationData conditionCreationData);
	void SetConditionSentence(UGC_ConditionSentence* newConditionSentence);

	FOnConditionSentenceChecked& GetOnConditionSentenceChecked();

	virtual void ProvideAditionalData(UObject* aditionalData) override;

	const UGC_ConditionSentence* GetConditionSentence();

protected:
	void OnPooledObjectCreated(FDataTableRowHandle creationDataHandle) override;


	void OnPooledObjectDestroyed() override;

};
