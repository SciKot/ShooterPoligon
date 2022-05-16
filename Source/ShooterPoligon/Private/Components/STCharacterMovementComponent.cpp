// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.


#include "Components/STCharacterMovementComponent.h"
#include "Player/SPBaseCharacter.h"

float USTCharacterMovementComponent::GetMaxSpeed() const
{
    const float MaxSpeed = Super::GetMaxSpeed();
    return MaxSpeed;
}
