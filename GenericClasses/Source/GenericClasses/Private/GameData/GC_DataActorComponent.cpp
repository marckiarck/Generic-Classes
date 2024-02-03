
#include "GameData/GC_DataActorComponent.h"
#include "GenericClassesMinimals.h"

// Sets default values for this component's properties
UGC_DataActorComponent::UGC_DataActorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void UGC_DataActorComponent::BeginPlay()
{
	Super::BeginPlay();

	UGC_GameData* gameData = UGC_SingletonRegister::GetInstance<UGC_GameData>();
	gameData->SaveData<AActor>(saveCategory, saveIdentifier, GetOwner());
}


