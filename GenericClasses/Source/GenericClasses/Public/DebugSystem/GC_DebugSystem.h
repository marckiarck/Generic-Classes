// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SingletonRegister/GC_SingletonRegister.h"
#include "GC_DebugSystem.generated.h"

#define GC_CHECK(CHECK_SENTENCE, FAIL_MESSAGE) \
	if (CHECK_SENTENCE) \
	{ \
		UGC_DebugSystem* debugSystem = UGC_SingletonRegister::GetInstance<UGC_DebugSystem>(); \
		debugSystem->Check(false, FAIL_MESSAGE); \
	} \
	
#define GC_CHECK_AND_DO(CHECK_SENTENCE, FAIL_MESSAGE, FAIL_SENTENCE) \
	if (CHECK_SENTENCE) \
		{ \
			UGC_DebugSystem* debugSystem = UGC_SingletonRegister::GetInstance<UGC_DebugSystem>(); \
			debugSystem->Check(false, FAIL_MESSAGE); \
			FAIL_SENTENCE; \
		} \

UCLASS()
class GENERICCLASSES_API UGC_DebugSystem : public UObject
{
	GENERATED_BODY()

public:
	void Check(bool checkSentence, FString failMessage);
	void SendLog(FString logMessage);
};
