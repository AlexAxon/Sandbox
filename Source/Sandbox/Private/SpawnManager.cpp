// ITHub 2026


#include "SpawnManager.h"


ASpawnManager::ASpawnManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();
	if (UWorld* World = GetWorld())
	{
		for (int i = 0; i < 10; ++i)
		{
			const FTransform SpawnTransform = FTransform(FRotator::ZeroRotator, FVector(0.0f, 150.0f * i, 0.0f));
			World->SpawnActor(SpawnClass, &SpawnTransform);
		}
	}
}

void ASpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

