
#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GenericClasses/Public/SingletonRegister/GC_SingletonRegister.h"
#include "GC_GameInstance.generated.h"


UCLASS()
class GENERICCLASSES_API UGC_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Transient)
	UGC_SingletonRegister* singletonInstance = nullptr;
};
