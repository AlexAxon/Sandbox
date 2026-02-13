// ITHub 2026


#include "BaseActor.h"

DEFINE_LOG_CATEGORY_STATIC(LogMain, Error, Error);

ABaseActor::ABaseActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseActor::BeginPlay()
{
	Super::BeginPlay();
	PrintTypes();
	
}

void ABaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalOffset(FVector(0, 0, 1));
}

void ABaseActor::PrintTypes()
{
	FString KillsStr = "Kills: " + FString::FromInt(Kills);
	FString HealthStr = "Health: " + FString::SanitizeFloat(Health);
	FString IsDeadStr = "Is dead " + FString(IsDead ? "true" : "false");

	FString Stat = FString::Printf(TEXT("\n \n +++ Stat +++ \n %s \n %s \n %s \n %s "), 
									*Name, *KillsStr, *HealthStr, *IsDeadStr);

	UE_LOG(LogMain, Error, TEXT("%s"), *Stat);
	UE_LOG(LogMain, Error, TEXT("   Actor name: %s"), *GetName());
	//UE_LOG(LogMain, Error, TEXT("Kills: %i"), Kills);
	//UE_LOG(LogMain, Error, TEXT("Health: %.2f"), Health);
	//UE_LOG(LogMain, Error, TEXT("IsDead: %d"), IsDead);
	//UE_LOG(LogMain, Error, TEXT("IsDead: %d"), static_cast<int>(IsDead));

	GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, Stat);
}

