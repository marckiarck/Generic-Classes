

#pragma once

#include "CoreMinimal.h"
#include "GC_DebugObject.generated.h"

UCLASS()
class GENERICCLASSESDEBUG_API UGC_DebugObject : public UObject
{
	GENERATED_BODY()

public:
	virtual void CollectDebugData();
	virtual void GetDebugString(FString& debugString);
};
