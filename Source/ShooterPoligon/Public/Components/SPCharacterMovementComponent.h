// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SPCharacterMovementComponent.generated.h"

/**
 *
 */
UCLASS()
class SHOOTERPOLIGON_API USPCharacterMovementComponent : public UCharacterMovementComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = 1.0f, ClampMax = 100.0f))
    float SpeedModifayer = 2.0f;

    virtual float GetMaxSpeed() const override;
};
