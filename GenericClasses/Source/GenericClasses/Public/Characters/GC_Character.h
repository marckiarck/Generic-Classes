// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericClasses/Public/ObjectPooler/GC_PooledObjectInterface.h"
#include "GC_Character.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct GENERICCLASSES_API FGC_CharacterSpawnData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
	class USkeletalMesh* skeletalmesh;

};

USTRUCT(BlueprintType, Blueprintable)
struct GENERICCLASSES_API FGC_CharacterSpawnRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, Category = Character)
	FGC_CharacterSpawnData characterSpawnData;

	UPROPERTY(EditAnywhere, Category = Controller)
		TSubclassOf<AController> characterController;
		
	UPROPERTY(EditAnywhere,Category = Controller, meta = (RowType = "GC_ControllerSpawnRow"))
		FDataTableRowHandle controllerData;
};

UCLASS(BlueprintType, Blueprintable)
class GENERICCLASSES_API AGC_Character : public ACharacter, public IGC_PooledObjectInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGC_Character();

public:
	void ApplyCharacterSpawnData(const FGC_CharacterSpawnData& spawnData);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnPooledObjectCreated(FDataTableRowHandle creationDataHandle) override;
	virtual void OnPooledObjectDestroyed() override;

};
