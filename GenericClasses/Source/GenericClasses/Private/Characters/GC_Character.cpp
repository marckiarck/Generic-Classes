#include "GenericClasses/Public/Characters/GC_Character.h"
#include "GenericClasses/Public/GenericClassesMinimals.h"

// Sets default values
AGC_Character::AGC_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AGC_Character::ApplyCharacterSpawnData(const FGC_CharacterSpawnData& spawnData)
{
	if (spawnData.skeletalmesh)
	{
		GetMesh()->SetSkeletalMesh(spawnData.skeletalmesh);
	}
}

// Called when the game starts or when spawned
void AGC_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGC_Character::OnPooledObjectCreated(FDataTableRowHandle creationDataHandle)
{
	FGC_CharacterSpawnRow* characterSpawnRow = GetRow<FGC_CharacterSpawnRow>(creationDataHandle);

	if (characterSpawnRow)
	{
		ApplyCharacterSpawnData(characterSpawnRow->characterSpawnData);

		TSubclassOf<AController> characterClass = characterSpawnRow->characterController;
		if (characterClass->IsValidLowLevel())
		{
			UGC_ObjectPooler* objectPooler = UGC_SingletonRegister::GetInstance<UGC_ObjectPooler>();
			AController* controller = objectPooler->SpawnActor<AController>(GetLevel(), characterClass, GetActorTransform(), characterSpawnRow->controllerData);
			controller->Possess(this);
		}
		
	}
}

void AGC_Character::OnPooledObjectDestroyed()
{
	
}

