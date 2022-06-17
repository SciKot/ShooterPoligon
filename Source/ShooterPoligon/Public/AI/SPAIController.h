// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#pragma once

#include "AIController.h"
#include "CoreMinimal.h"

#include "SPAIController.generated.h"

class USPAIPerceptionComponent;

UCLASS()
class SHOOTERPOLIGON_API ASPAIController : public AAIController
{
	GENERATED_BODY()

public:
	ASPAIController();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USPAIPerceptionComponent* SPAIPerceptionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName FocusOnKeyName = "EnemyActor";

	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;

private:
	AActor* GetActorToFocusOn() const;
};
