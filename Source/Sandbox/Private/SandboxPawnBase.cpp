// ITHub 2026


#include "SandboxPawnBase.h"

// Sets default values
ASandboxPawnBase::ASandboxPawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(SceneComponent);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	StaticMeshComponent->SetupAttachment(SceneComponent);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(SceneComponent);
}

void ASandboxPawnBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void ASandboxPawnBase::UnPossessed()
{
	Super::UnPossessed();
}

// Called when the game starts or when spawned
void ASandboxPawnBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASandboxPawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(!VelocityVector.IsZero())
	{
		FVector NewLocation = GetActorLocation() + VelocityVector * DeltaTime * MovementSpeed;
		SetActorLocation(NewLocation);
		VelocityVector = FVector::ZeroVector;
	}
}

// Called to bind functionality to input
void ASandboxPawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ASandboxPawnBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASandboxPawnBase::MoveRight);

}

void ASandboxPawnBase::MoveForward(float Value)
{
	VelocityVector.X = Value;
}

void ASandboxPawnBase::MoveRight(float Value)
{
	VelocityVector.Y = Value;
}

