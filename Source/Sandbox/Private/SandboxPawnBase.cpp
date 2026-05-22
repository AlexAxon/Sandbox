// ITHub 2026

#include "SandboxPawnBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"

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
	Movement(DeltaTime);
	TraceFromCamera();
}

// Called to bind functionality to input
void ASandboxPawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// Axis for move and rotate
	PlayerInputComponent->BindAxis("MoveForward", this, &ASandboxPawnBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASandboxPawnBase::MoveRight);
	PlayerInputComponent->BindAxis("Yaw", this, &ASandboxPawnBase::Turn);
	PlayerInputComponent->BindAxis("Pitch", this, &ASandboxPawnBase::LookUp);
	// Delete and simulate physics event
	PlayerInputComponent->BindAction("LeftClick", IE_Pressed, this, &ASandboxPawnBase::OnLeftClick);
	PlayerInputComponent->BindAction("RightClick", IE_Pressed, this, &ASandboxPawnBase::OnRightClick);
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

void ASandboxPawnBase::Movement(float DeltaTime)
{
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

void ASandboxPawnBase::TraceFromCamera()
{
	if (!CameraComponent){ return;}
	
	const FVector StartLocation = CameraComponent->GetComponentLocation();
	const FVector ForwardVector = CameraComponent->GetForwardVector();
	
	const float TraceDistance = 1000.0f;
	const FVector EndLocation = StartLocation + ForwardVector * TraceDistance;
	
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);
	TraceParams.bTraceComplex = true;
	
	FHitResult HitResult;
	const bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult, 
		StartLocation, 
		EndLocation, 
		ECC_Visibility, 
		TraceParams);
	
	//DrawDebugLine(GetWorld(), 
	//	StartLocation, 
	//	EndLocation, 
	//	bHit ? FColor::Green : FColor::Red,
	//	false,
	//	0.0f,
	//	0,
	//	2.0f);
	
	if (bHit && HitResult.GetActor())
	{
		CurrentHitActor = HitResult.GetActor();
		
		FString HitActorName = HitResult.GetActor()->GetName();
		
		UKismetSystemLibrary::PrintString(GetWorld(), HitActorName, true, true, FLinearColor::Red, 0.0f);
	}
	else
	{
		CurrentHitActor = nullptr;
	}
}

void ASandboxPawnBase::OnLeftClick()
{
	if (CurrentHitActor && CurrentHitActor->IsValidLowLevel())
	{
		CurrentHitActor->Destroy();
		CurrentHitActor = nullptr;
		
		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Actor destroyed!"), true, true, FLinearColor::Green, 1.0f);
	}
	else
	{
		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("No actor to destroy!"), true, true, FLinearColor::Yellow, 1.0f);
	}
}

void ASandboxPawnBase::OnRightClick()
{
	if (CurrentHitActor && CurrentHitActor->IsValidLowLevel())
	{
		UPrimitiveComponent* PrimitiveComponent = CurrentHitActor->FindComponentByClass<UPrimitiveComponent>();
		if (PrimitiveComponent)
		{
			PrimitiveComponent->SetSimulatePhysics(true);
			
			UKismetSystemLibrary::PrintString(GetWorld(), 
				FString::Printf(TEXT("Physics enabled for: %s"), *CurrentHitActor->GetName()), 
				true, true, FLinearColor::Blue, 1.0f);
		}
		else
		{
			UKismetSystemLibrary::PrintString(GetWorld(), 
				FString::Printf(TEXT("Actor %s has no primitive component!"), *CurrentHitActor->GetName()), 
				true, true, FLinearColor::Red, 1.0f);
		}
	}
	else
	{
		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("No actor to enable physics!"), true, true, FLinearColor::Yellow, 1.0f);
	}
}