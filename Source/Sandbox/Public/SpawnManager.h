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

	UPROPERTY(EditAnywhere)
	UClass* SpawnClass;
};
