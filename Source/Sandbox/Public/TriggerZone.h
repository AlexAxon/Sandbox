// ITHub 2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TriggerZone.generated.h"


UCLASS()
class SANDBOX_API ATriggerZone : public AActor
{
	GENERATED_BODY()
	
public:	
	ATriggerZone();

protected:
	virtual void BeginPlay() override;
	
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* TriggerBox;
	
	UFUNCTION()
	void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
