
#if WITH_GAMEPLAY_DEBUGGER

#include "GenericClassesDebug/GameplayDebugger/DebugObjects/GC_DebugObjectCategory.h"
#include "GenericClassesMinimals.h"

FGC_DebugObjectCategory::FGC_DebugObjectCategory()
{
	bShowOnlyWithDebugActor = false;
}

void FGC_DebugObjectCategory::CollectData(APlayerController* OwnerPC, AActor* DebugActor)
{
	UGC_DebugObjectManager* debugObjectManager = UGC_SingletonRegister::GetInstance<UGC_DebugObjectManager>();
	if (debugObjectManager)
	{
		debugObject = debugObjectManager->GetMainDebugObject();
		debugObject->CollectDebugData();
	}
	
}

void FGC_DebugObjectCategory::DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext)
{
	if (debugObject)
	{
		FString debugString;
		debugObject->GetDebugString(debugString);

		CanvasContext.Printf(TEXT("%s"), *debugString);
	}
	else
	{
		CanvasContext.Printf(TEXT("{red}[---- No Debug Object selected ----] \n"));
	}
	
}

TSharedRef<FGameplayDebuggerCategory> FGC_DebugObjectCategory::MakeInstance()
{
	return MakeShareable(new FGC_DebugObjectCategory());
}

#endif //WITH_GAMEPLAY_DEBUGGER