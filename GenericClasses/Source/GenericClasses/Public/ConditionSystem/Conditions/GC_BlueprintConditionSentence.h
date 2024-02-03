// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ConditionSystem/Conditions/GC_ConditionSentence.h"
#include "GC_BlueprintConditionSentence.generated.h"


UCLASS(BlueprintType, Blueprintable)
class UGC_BlueprintConditionSentence : public UGC_ConditionSentence
{
	GENERATED_BODY()
	
public:
	virtual bool RunConditionSentence() override;

	UFUNCTION(BlueprintImplementableEvent, DisplayName = CheckCondition)
	bool RunConditionSentence_BP();
};
