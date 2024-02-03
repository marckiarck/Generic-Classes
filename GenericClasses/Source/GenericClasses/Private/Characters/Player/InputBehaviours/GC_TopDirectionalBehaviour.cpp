
#include "GenericClasses/Public/Characters/Player/InputBehaviours/GC_TopDirectionalBehaviour.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"

void UGC_TopDirectionalBehaviour::BindInputActions(UEnhancedInputComponent* enchancedInputComponent)
{
	Super::BindInputActions(enchancedInputComponent);

	if (enchancedInputComponent == nullptr)
	{
		UGC_DebugSystem* debugSystem = UGC_SingletonRegister::GetInstance<UGC_DebugSystem>();
		debugSystem->SendLog(TEXT("Failed to bind actions"));
		return;
	}

	enchancedInputComponent->BindAction(upMoveAction, ETriggerEvent::Triggered, this, &UGC_TopDirectionalBehaviour::OnPressedUp);
	enchancedInputComponent->BindAction(downMoveAction, ETriggerEvent::Triggered, this, &UGC_TopDirectionalBehaviour::OnPressedDown);
	enchancedInputComponent->BindAction(rightMoveAction, ETriggerEvent::Triggered, this, &UGC_TopDirectionalBehaviour::OnPressedRight);
	enchancedInputComponent->BindAction(leftMoveAction, ETriggerEvent::Triggered, this, &UGC_TopDirectionalBehaviour::OnPressedLeft);
}

void UGC_TopDirectionalBehaviour::OnPressedUp()
{
	playerPawn->AddMovementInput(upVector);
}

void UGC_TopDirectionalBehaviour::OnPressedDown()
{
	playerPawn->AddMovementInput(upVector * -1.f);
}

void UGC_TopDirectionalBehaviour::OnPressedRight()
{
	playerPawn->AddMovementInput(rightVector);
}

void UGC_TopDirectionalBehaviour::OnPressedLeft()
{
	playerPawn->AddMovementInput(rightVector * -1.f);
}
