#include "BaseActor.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"

DEFINE_LOG_CATEGORY_STATIC(LogMain, Error, Error);

ABaseActor::ABaseActor()
{
	PrimaryActorTick.bCanEverTick = true;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(MeshComp);
}

void ABaseActor::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
	PrintTransform();
	
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (PlayerCharacter)
	{
		PlayerStartLocation = PlayerCharacter->GetActorLocation();
	}
	
	if (ChangeColor)
	{
		DynamicMaterial = MeshComp->CreateAndSetMaterialInstanceDynamic(0);
		GetWorldTimerManager().SetTimer(ColorTimerHandle, this, &ABaseActor::SetRandomColor, TimerRate, true);
	}
}

void ABaseActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	Movement();
}

void ABaseActor::MoveTowardsPlayer(float DeltaTime)
{
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!PlayerCharacter) return;
	
	CurrentMovementTime += DeltaTime;
	
	if (CurrentMovementTime >= 2.0f)
	{
		bMovingAway = !bMovingAway;
		CurrentMovementTime = 0.0f;
	}

	FVector PlayerLocation = PlayerCharacter->GetActorLocation();
	FVector ToPlayer = PlayerLocation - StartLocation;
	ToPlayer.Normalize();

	float SinValue = FMath::Sin(MovementSettings.Frequency * GetWorld()->GetTimeSeconds());
	float MovementDistance = MovementSettings.Amplitude * SinValue;
	
	if (bMovingAway)
	{
		SetActorLocation(StartLocation - ToPlayer * MovementDistance);
	}
	else
	{
		SetActorLocation(StartLocation + ToPlayer * MovementDistance);
	}
}

void ABaseActor::PrintStats() const
{
	const FString KillsStr = "Kills: " + FString::FromInt(Kills);
	const FString HealthStr = "Health: " + FString::SanitizeFloat(Health);
	const FString IsDeadStr = "Is dead " + FString(IsDead ? "true" : "false");

	const FString Stats = FString::Printf(TEXT("\n \n +++ Stat +++ \n %s \n %s \n %s \n %s "), 
		*Name, *KillsStr, *HealthStr, *IsDeadStr);

	UE_LOG(LogMain, Error, TEXT("   Actor name: %s"), *GetName());
	UE_LOG(LogMain, Error, TEXT("%s"), *Stats);

	GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, Stats);
}

void ABaseActor::PrintTransform() const
{
	const FTransform Transform = GetActorTransform();
	const FVector Location = Transform.GetLocation();
	const FRotator Rotator = Transform.Rotator();
	const FVector Scale = Transform.GetScale3D();
	
	UE_LOG(LogMain, Error, TEXT("Actor name %s"), *GetName());
	UE_LOG(LogMain, Error, TEXT("Transform %s"), *Transform.ToString());
	UE_LOG(LogMain, Error, TEXT("Location %s"), *Location.ToString());
	UE_LOG(LogMain, Error, TEXT("Rotator %s"), *Rotator.ToString());
	UE_LOG(LogMain, Error, TEXT("Scale %s"), *Scale.ToString());
	UE_LOG(LogMain, Error, TEXT("Readable transform %s"), *Transform.ToHumanReadableString());
}

void ABaseActor::Movement()
{
	float Time = GetWorld()->GetTimeSeconds();

	switch (MovementSettings.MovementType)
	{
	case EMovementType::Static:
		break;
	case EMovementType::SinVertical:
		{
			FVector CurrentLocation = GetActorLocation();
			CurrentLocation.Z = StartLocation.Z + MovementSettings.Amplitude * FMath::Sin(MovementSettings.Frequency * Time);
			SetActorLocation(CurrentLocation);
			break;
		}
	case EMovementType::SinHorizontalX:
		{
			FVector CurrentLocation = GetActorLocation();
			CurrentLocation.X = StartLocation.X + MovementSettings.Amplitude * FMath::Sin(MovementSettings.Frequency * Time);
			SetActorLocation(CurrentLocation);
			break;
		}
	case EMovementType::SinHorizontalY:
		{
			FVector CurrentLocation = GetActorLocation();
			CurrentLocation.Y = StartLocation.Y + MovementSettings.Amplitude * FMath::Sin(MovementSettings.Frequency * Time);
			SetActorLocation(CurrentLocation);
			break;
		}
	case EMovementType::Up:
		{
			AddActorLocalOffset(FVector::UnitZ());
			break;
		}
	}
}

void ABaseActor::SetRandomColor()
{
	if (DynamicMaterial)
	{
		DynamicMaterial->SetVectorParameterValue("BaseColor", FLinearColor::MakeRandomColor());
	}
}