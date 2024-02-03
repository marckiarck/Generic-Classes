
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GC_DataActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GENERICCLASSES_API UGC_DataActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGC_DataActorComponent();

private:
	UPROPERTY(EditAnywhere, Category=GameData)
	FString saveCategory;

	UPROPERTY(EditAnywhere, Category=GameData)
	FString saveIdentifier;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
};
