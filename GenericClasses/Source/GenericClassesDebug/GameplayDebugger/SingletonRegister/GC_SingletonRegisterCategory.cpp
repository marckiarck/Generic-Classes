#include "GenericClassesDebug/GameplayDebugger/SingletonRegister/GC_SingletonRegisterCategory.h"
#include "SingletonRegister/GC_SingletonRegister.h"

#if WITH_GAMEPLAY_DEBUGGER

FGC_SingletonRegisterCategory::FGC_SingletonRegisterCategory()
{
	bShowOnlyWithDebugActor = false;
}

void FGC_SingletonRegisterCategory::CollectData(APlayerController* OwnerPC, AActor* DebugActor)
{
	UGC_SingletonRegister* singletonRegister = UGC_SingletonRegister::GetSingletonRegister();
	if (singletonRegister)
	{
		singletonName = singletonRegister->GetName();
		registeredSingletonsMap = singletonRegister->GetRegisteredSingletonMap();
	}
}

void FGC_SingletonRegisterCategory::DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext)
{
	CanvasContext.Printf(TEXT("{Green}Singleton Instance: %s"), *singletonName);

	TArray<FName> singeltonKeys;
	registeredSingletonsMap.GetKeys(singeltonKeys);
	for (const FName singletonKey : singeltonKeys)
	{
		const UObject* keyObject = registeredSingletonsMap[singletonKey];
		FString objectKey = singletonKey.ToString();
		if (keyObject || keyObject->IsValidLowLevel())
		{
			FString objectName = keyObject->GetName();
			CanvasContext.Printf(TEXT("{Yellow}%s: %s"),* objectKey, *objectName);
		}
		else
		{
			CanvasContext.Printf(TEXT("{Red}%s: NULL"), *objectKey);
		}
	}
}

TSharedRef<FGameplayDebuggerCategory> FGC_SingletonRegisterCategory::MakeInstance()
{
	return MakeShareable(new FGC_SingletonRegisterCategory());
}

#endif //WITH_GAMEPLAY_DEBUGGER