// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "AI/SPAIController.h"

#include "AI/SPAICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SPAIPerceptionComponent.h"
#include "Components/SPRespawnComponent.h"

ASPAIController::ASPAIController()
{
	SPAIPerceptionComponent = CreateDefaultSubobject<USPAIPerceptionComponent>("SPPerceptionComponent");
	SetPerceptionComponent(*SPAIPerceptionComponent);

	RespawnComponent = CreateDefaultSubobject<USPRespawnComponent>("RespawnComponent");

	bWantsPlayerState = true;
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
	SetFocus(GetActorToFocusOn());
}

AActor* ASPAIController::GetActorToFocusOn() const
{
	if (!GetBlackboardComponent()) return nullptr;
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
