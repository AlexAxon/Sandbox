// ITHub 2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnManager.generated.h"

UCLASS()
class SANDBOX_API ASpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnManager();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, Category = "Spawn")
	UClass* SpawnClass;

	//Параметры стенки
	UPROPERTY(EditAnywhere, Category = "Wall")
	int32 WidthCount = 5;  //Кол-во кубов в ширину
	
	UPROPERTY(EditAnywhere, Category = "Wall")
	int32 HeightCount = 5;  //Кол-во кубов в высоту
	
	UPROPERTY(EditAnywhere, Category = "Wall")
	float Spacing = 200.0f;  //Расстояние между кубами

	//Парам TimerRate для смены цвета
	UPROPERTY(EditAnywhere, Category = "Color")
	float MinTimerRate = 1.0f;
	
	UPROPERTY(EditAnywhere, Category = "Color")
	float MaxTimerRate = 5.0f;

	//Парам move (от/к игроку)
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MinAmplitude = 50.0f;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MaxAmplitude = 200.0f;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MinFrequency = 0.5f;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MaxFrequency = 3.0f;

private:
	FVector GetSpawnPosition(int32 XIndex, int32 YIndex) const;
};