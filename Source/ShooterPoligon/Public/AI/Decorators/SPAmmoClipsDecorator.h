// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#pragma once

#include "BehaviorTree/BTDecorator.h"
#include "CoreMinimal.h"

#include "SPAmmoClipsDecorator.generated.h"

class ASPBaseWeapon;

UCLASS()
class SHOOTERPOLIGON_API USPAmmoClipsDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:
	USPAmmoClipsDecorator();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TSubclassOf<ASPBaseWeapon> WeaponType;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
