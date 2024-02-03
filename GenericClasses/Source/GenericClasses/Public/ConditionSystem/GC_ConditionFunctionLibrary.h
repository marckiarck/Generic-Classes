// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EventSystem/Events/GC_Event.h"
#include "GC_ConditionFunctionLibrary.generated.h"


DECLARE_DYNAMIC_DELEGATE(FOnConditionResult);

UCLASS()
class GENERICCLASSES_API UGC_ConditionFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "ConditionSystem", meta = (BlueprintInternalUseOnly = "true"))
		static void CheckCondition(TSubclassOf<class UGC_ConditionSentence> conditionClass, const FOnConditionResult OnTrue, const FOnConditionResult OnFalse, UObject* aditionalData = nullptr);

	UFUNCTION(BlueprintCallable, Category = "ConditionSystem", meta = (BlueprintInternalUseOnly = "true"))
		static void WaitConditionSuccess(TSubclassOf<class UGC_ConditionSentence> conditionClass, const FOnConditionResult OnSuccess, const FOnConditionResult OnTimeOut, float conditionCheckDuration = -1.f, UObject* aditionalData = nullptr);
};
