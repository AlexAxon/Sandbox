// ITHub 2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SandboxPlayerControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOX_API ASandboxPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
	
	protected:
		virtual void SetupInputComponent() override;
		virtual void BeginPlay() override;
	
	private:
		void ChangePawn();
	
		UPROPERTY()
		TArray<AActor*> Pawns;
	
	 int32 CurrentPawnIndex = 0;
};
