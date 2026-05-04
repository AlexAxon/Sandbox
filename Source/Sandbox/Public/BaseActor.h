#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "BaseActor.generated.h"

UENUM(BlueprintType)
enum class EMovementType : uint8
{
	SinVertical,
	SinHorizontalX,
	SinHorizontalY,
	Static,
	Up
};

USTRUCT(BlueprintType)
struct FMovementSettings
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	EMovementType MovementType = EMovementType::Static;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float Amplitude = 50.0f;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float Frequency = 2.0f;
};

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
	void PrintStats() const;
	
	void PrintTransform() const;
	
	void Movement();
	
	void SetRandomColor();

public:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;
	
	UPROPERTY(VisibleAnywhere, Category = "Stats")
	int32 Kills = 5;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float Health = 50.15;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	bool IsDead = false;

	UPROPERTY(EditInstanceOnly, Category = "Stats")
	FString Name = "Alex";
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	FMovementSettings MovementSettings;
	
	UPROPERTY(EditAnywhere, Category = "Color")
	bool ChangeColor = false;
	
	UPROPERTY(EditAnywhere, Category = "Color")
	float TimerRate = 2.0f;
	
private:
	FVector StartLocation;
	FTimerHandle TimerHandle;
	UPROPERTY()
	UMaterialInstanceDynamic* DynamicMaterial;
};
