// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "AI/SPAICharacter.h"

#include "AI/SPAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

ASPAICharacter::ASPAICharacter(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ASPAIController::StaticClass();

	bUseControllerRotationYaw = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
	}
}
