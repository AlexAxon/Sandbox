// ITHub 2026

#include "SandboxPawnBase.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ASandboxPawnBase::ASandboxPawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(SceneComponent);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	StaticMeshComponent->SetupAttachment(SceneComponent);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(SceneComponent);
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->bInheritPitch = true;
	SpringArmComponent->bInheritYaw = true;
	SpringArmComponent->bInheritRoll = true;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(SpringArmComponent);
	
	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = true;
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
	
	APlayerController* PlayerController = GetController<APlayerController>();
	if(PlayerController)
	{
		PlayerController->bShowMouseCursor = false;
		PlayerController->bEnableClickEvents = true;
		PlayerController->bEnableMouseOverEvents = true;
		
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->SetShowMouseCursor(false);
	}
}

// Called every frame
void ASandboxPawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(!VelocityVector.IsZero())
	{
		FVector ForwardDirection = GetControlRotation().Vector();
		ForwardDirection.Z = 0;
		ForwardDirection.Normalize();
		
		FVector RightDirection = GetControlRotation().Quaternion().GetRightVector();
		RightDirection.Z = 0;
		RightDirection.Normalize();
		
		FVector NewLocation = GetActorLocation() + 
			(ForwardDirection * VelocityVector.X + RightDirection * VelocityVector.Y) * 
			DeltaTime * MovementSpeed;
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
	PlayerInputComponent->BindAxis("Turn", this, &ASandboxPawnBase::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ASandboxPawnBase::LookUp);
}

void ASandboxPawnBase::MoveForward(float Value)
{
	VelocityVector.X = Value;
}

void ASandboxPawnBase::MoveRight(float Value)
{
	VelocityVector.Y = Value;
}

void ASandboxPawnBase::Turn(float Value)
{
	AddControllerYawInput(Value * MouseSensitivity);
}

void ASandboxPawnBase::LookUp(float Value)
{
	AddControllerPitchInput(Value * MouseSensitivity);
}