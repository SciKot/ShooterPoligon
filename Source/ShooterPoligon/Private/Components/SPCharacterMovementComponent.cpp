// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.


#include "Components/SPCharacterMovementComponent.h"
#include "Player/SPBaseCharacter.h"

float USPCharacterMovementComponent::GetMaxSpeed() const
{
    const float MaxSpeed = Super::GetMaxSpeed();
    const ASPBaseCharacter* Player = Cast<ASPBaseCharacter>(GetPawnOwner());
    return Player && Player->isRunning() ? MaxSpeed * SpeedModifayer : MaxSpeed;
}
