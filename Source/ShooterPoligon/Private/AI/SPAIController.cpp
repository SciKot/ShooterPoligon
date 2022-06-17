// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "AI/SPAIController.h"

#include "AI/SPAICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SPAIPerceptionComponent.h"

ASPAIController::ASPAIController()
{
	SPAIPerceptionComponent = CreateDefaultSubobject<USPAIPerceptionComponent>("SPPerceptionComponent");
	SetPerceptionComponent(*SPAIPerceptionComponent);
}

void ASPAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto SPCharacter = Cast<ASPAICharacter>(InPawn);
	if (SPCharacter)
	{
		RunBehaviorTree(SPCharacter->BehaviorTreeAsset);
	}
}

void ASPAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const auto AimActor = GetActorToFocusOn();
	SetFocus(AimActor);
}

AActor* ASPAIController::GetActorToFocusOn() const
{
	if (!GetBlackboardComponent()) return nullptr;
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
