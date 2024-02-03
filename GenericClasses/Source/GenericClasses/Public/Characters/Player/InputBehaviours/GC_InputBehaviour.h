

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GenericClasses/Public/Characters/Controllers/GC_PlayerController.h"
#include "EnhancedInputComponent.h"
#include "GC_InputBehaviour.generated.h"


UCLASS(editinlinenew, DefaultToInstanced)
class GENERICCLASSES_API UGC_InputBehaviour : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(Transient)
	APawn* playerPawn = nullptr;

public:
	virtual void BindInputActions(UEnhancedInputComponent* enchancedInputComponent);
	virtual void ConfigurePlayerController(AGC_PlayerController* playerController);
};
