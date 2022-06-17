// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#pragma once

#include "BehaviorTree/BTDecorator.h"
#include "CoreMinimal.h"

#include "SPHealthPercentDecorator.generated.h"

UCLASS()
class SHOOTERPOLIGON_API USPHealthPercentDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:
	USPHealthPercentDecorator();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float HealthPercent = 0.6f;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
