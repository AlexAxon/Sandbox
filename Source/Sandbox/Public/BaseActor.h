// ITHub 2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseActor.generated.h"

UCLASS()
class SANDBOX_API ABaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	void PrintTypes();

public:
	UPROPERTY(VisibleAnywhere, Category = "Stats")
	int32 Kills = 5;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float Health = 50.15;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	bool IsDead = false;

	UPROPERTY(EditInstanceOnly, Category = "Stats")
	FString Name = "Alex";

};
