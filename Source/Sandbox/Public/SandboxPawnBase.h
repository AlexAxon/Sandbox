// ITHub 2026

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "SandboxPawnBase.generated.h"

UCLASS()
class SANDBOX_API ASandboxPawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASandboxPawnBase();
	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComponent;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent;
	
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;
	
	UPROPERTY(VisibleAnywhere)
	float MovementSpeed = 600.0f;
	
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
private:
	FVector VelocityVector = FVector::ZeroVector;
	
	void MoveForward(float Value);
	void MoveRight(float Value);
};
