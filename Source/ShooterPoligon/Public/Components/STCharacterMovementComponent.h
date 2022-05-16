// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "STCharacterMovementComponent.generated.h"

/**
 *
 */
UCLASS()
class SHOOTERPOLIGON_API USTCharacterMovementComponent : public UCharacterMovementComponent
{
    GENERATED_BODY()

public:
    virtual float GetMaxSpeed() const override;
};
