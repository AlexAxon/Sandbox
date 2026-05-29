// ITHub 2026


#include "TriggerZone.h"

#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"

ATriggerZone::ATriggerZone()
{
	PrimaryActorTick.bCanEverTick = false;
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	SetRootComponent(TriggerBox);
	TriggerBox->SetBoxExtent(FVector(150.0f, 150.0f, 100.0f));
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetCollisionObjectType(ECC_WorldDynamic);
	TriggerBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	TriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	TriggerBox->SetGenerateOverlapEvents(true);
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ATriggerZone::OnTriggerBeginOverlap);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ATriggerZone::OnTriggerEndOverlap);
}

void ATriggerZone::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATriggerZone::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	UKismetSystemLibrary::PrintString(GetWorld(), 
			FString::Printf(TEXT("Begin overlap with %s"), *OtherActor->GetName()), 
			true, true, FLinearColor::Blue, 3.0f);
}

void ATriggerZone::OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UKismetSystemLibrary::PrintString(GetWorld(), 
			FString::Printf(TEXT("End overlap with %s"), *OtherActor->GetName()), 
			true, true, FLinearColor::Blue, 3.0f);
}


