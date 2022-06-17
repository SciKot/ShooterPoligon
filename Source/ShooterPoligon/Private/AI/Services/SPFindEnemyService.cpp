// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "AI/Services/SPFindEnemyService.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SPAIPerceptionComponent.h"
#include "SPUtils.h"

USPFindEnemyService::USPFindEnemyService()
{
	NodeName = "Find Enemy";
}

void USPFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard)
	{
		const auto Controller = OwnerComp.GetAIOwner();
		const auto PerceptionComponent = SPUtils::GetSPPlayerComponent<USPAIPerceptionComponent>(Controller);
		if (PerceptionComponent)
		{
			Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
