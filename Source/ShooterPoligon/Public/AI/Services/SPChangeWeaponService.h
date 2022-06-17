// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#pragma once

#include "BehaviorTree/BTService.h"
#include "CoreMinimal.h"

#include "SPChangeWeaponService.generated.h"

UCLASS()
class SHOOTERPOLIGON_API USPChangeWeaponService : public UBTService
{
	GENERATED_BODY()

public:
	USPChangeWeaponService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (ClampMin = 0.0f, ClampMax = 1.0f))
	float ChangeProbability = 0.8f;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
