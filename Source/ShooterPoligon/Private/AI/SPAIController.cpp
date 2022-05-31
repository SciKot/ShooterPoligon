// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "AI/SPAIController.h"

#include "AI/SPAICharacter.h"

void ASPAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto SPCharacter = Cast<ASPAICharacter>(InPawn);
	if (SPCharacter)
	{
		RunBehaviorTree(SPCharacter->BehaviorTreeAsset);
	}
}
