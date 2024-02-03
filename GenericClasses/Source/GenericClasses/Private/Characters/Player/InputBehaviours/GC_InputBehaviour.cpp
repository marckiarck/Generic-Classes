
#include "GenericClasses/Public/Characters/Player/InputBehaviours/GC_InputBehaviour.h"

void UGC_InputBehaviour::BindInputActions(UEnhancedInputComponent* enchancedInputComponent)
{
}

void UGC_InputBehaviour::ConfigurePlayerController(AGC_PlayerController* playerController)
{
	playerPawn = playerController->GetPawn();
}