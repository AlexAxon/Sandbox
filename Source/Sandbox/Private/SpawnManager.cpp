// ITHub 2026

#include "SpawnManager.h"
#include "BaseActor.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

ASpawnManager::ASpawnManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();
	
	if (!SpawnClass)
	{
		UE_LOG(LogTemp, Error, TEXT("SpawnManager: SpawnClass is not set!"));
		return;
	}

	UWorld* World = GetWorld();
	if (!World) return;

	// Стенка кубов
	for (int32 Width = 0; Width < WidthCount; ++Width)
	{
		for (int32 Height = 0; Height < HeightCount; ++Height)
		{
			FVector SpawnLocation = GetSpawnPosition(Width, Height);
			
			// Спавн
			ABaseActor* SpawnedActor = World->SpawnActor<ABaseActor>(SpawnClass, SpawnLocation, FRotator::ZeroRotator);
			
			if (SpawnedActor)
			{
				// Рандом TimerRate для смены цвета
				float RandomTimerRate = FMath::RandRange(MinTimerRate, MaxTimerRate);
				SpawnedActor->TimerRate = RandomTimerRate;
				SpawnedActor->ChangeColor = true; // Смена цвета
				
				// Рандом параметры движения
				float RandomAmplitude = FMath::RandRange(MinAmplitude, MaxAmplitude);
				float RandomFrequency = FMath::RandRange(MinFrequency, MaxFrequency);
				
				SpawnedActor->MovementSettings.MovementType = EMovementType::SinHorizontalY; //Move по Y
				SpawnedActor->MovementSettings.Amplitude = RandomAmplitude;
				SpawnedActor->MovementSettings.Frequency = RandomFrequency;
			}
		}
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Spawned %d cubes (%d x %d)"), WidthCount * HeightCount, WidthCount, HeightCount);
}

FVector ASpawnManager::GetSpawnPosition(int32 WidthIndex, int32 HeightIndex) const
{
	// Позиция относительно SpawnManager
	FVector StartOffset = GetActorLocation();
	
	// Смещение по X и Z
	float XOffset = (WidthIndex - (WidthCount - 1) / 2.0f) * Spacing;
	float ZOffset = HeightIndex * Spacing;
	
	return StartOffset + FVector(XOffset, 0.0f, ZOffset);
}

void ASpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}