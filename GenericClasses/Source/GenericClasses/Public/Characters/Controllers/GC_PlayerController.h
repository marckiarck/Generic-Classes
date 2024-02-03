#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "GC_PlayerController.generated.h"


UCLASS()
class GENERICCLASSES_API AGC_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category= InputBehaviours)
	UInputMappingContext* behavioursMappingContext;

	UPROPERTY(EditAnywhere, Instanced, Category=InputBehaviours)
	class UGC_InputBehaviour* inputBehaviour;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
};
