

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GenericClasses/Public/Characters/Controllers/GC_PlayerController.h"
#include "EnhancedInputComponent.h"
#include "GenericClasses/Public/Characters/Player/InputBehaviours/GC_InputBehaviour.h"
#include "GC_TopDirectionalBehaviour.generated.h"


UCLASS(editinlinenew, DefaultToInstanced)
class GENERICCLASSES_API UGC_TopDirectionalBehaviour : public UGC_InputBehaviour
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	FVector upVector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	FVector rightVector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* upMoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* downMoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* rightMoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* leftMoveAction;

public:
	virtual void BindInputActions(UEnhancedInputComponent* enchancedInputComponent);

protected:
	virtual void OnPressedUp();
	virtual void OnPressedDown();
	virtual void OnPressedRight();
	virtual void OnPressedLeft();
};
