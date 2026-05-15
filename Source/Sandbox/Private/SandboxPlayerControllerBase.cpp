// ITHub 2026


#include "SandboxPlayerControllerBase.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SandboxPawnBase.h"

void ASandboxPlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("ChangePawn", IE_Released, this, &ASandboxPlayerControllerBase::ChangePawn);
}

void ASandboxPlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASandboxPawnBase::StaticClass(), Pawns);
}

void ASandboxPlayerControllerBase::ChangePawn()
{
	if (Pawns.Num() <= 1) return;
	
	ASandboxPawnBase* CurrentPawn = Cast<ASandboxPawnBase>(Pawns[CurrentPawnIndex]);
	CurrentPawnIndex = (CurrentPawnIndex + 1) % Pawns.Num();
	if (!CurrentPawn) return;
	
	Possess(CurrentPawn);
}
