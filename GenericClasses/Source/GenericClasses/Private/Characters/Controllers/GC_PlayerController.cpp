
#include "GenericClasses/Public/Characters/Controllers/GC_PlayerController.h"
#include "GenericClassesMinimals.h"
#include "EnhancedInputSubsystems.h"

void AGC_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(behavioursMappingContext, 0);
	}

	inputBehaviour->ConfigurePlayerController(this);
}

void AGC_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		inputBehaviour->BindInputActions(EnhancedInputComponent);
	}
	else
	{
		UGC_DebugSystem* debugSystem = UGC_SingletonRegister::GetInstance<UGC_DebugSystem>();
		FString playerControllerName;
		GetName(playerControllerName);
		debugSystem->SendLog(FString::Printf(TEXT("Failed to find Enhanced Input Component in %s Player Component"), *playerControllerName));
	}
}
