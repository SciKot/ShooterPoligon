// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#pragma once

#include "BehaviorTree/BTService.h"
#include "CoreMinimal.h"

#include "SPFindEnemyService.generated.h"

UCLASS()
class SHOOTERPOLIGON_API USPFindEnemyService : public UBTService
{
	GENERATED_BODY()

public:
	USPFindEnemyService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector EnemyActorKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
