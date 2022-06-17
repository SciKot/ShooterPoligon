// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#pragma once

#include "BehaviorTree/BTService.h"
#include "CoreMinimal.h"

#include "SPFireService.generated.h"

UCLASS()
class SHOOTERPOLIGON_API USPFireService : public UBTService
{
	GENERATED_BODY()

public:
	USPFireService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector EnemyActorKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
