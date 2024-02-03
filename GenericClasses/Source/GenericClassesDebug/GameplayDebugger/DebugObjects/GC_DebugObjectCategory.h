
#pragma once

#if WITH_GAMEPLAY_DEBUGGER

#include "CoreMinimal.h"
#include "GameplayDebuggerCategory.h"


class GENERICCLASSESDEBUG_API FGC_DebugObjectCategory : public FGameplayDebuggerCategory
{
public:
	FGC_DebugObjectCategory();

private:
	UGC_DebugObject* debugObject;

public:
	void CollectData(APlayerController* OwnerPC, AActor* DebugActor) override;
	void DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext) override;

	static TSharedRef<FGameplayDebuggerCategory> MakeInstance();
};

#endif //WITH_GAMEPLAY_DEBUGGER