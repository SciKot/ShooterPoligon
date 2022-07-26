// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "Components/SPAIPerceptionComponent.h"

#include "AIController.h"
#include "Components/SPHealthComponent.h"
#include "Perception/AISense_Damage.h"
#include "Perception/AISense_Sight.h"
#include "SPUtils.h"

AActor* USPAIPerceptionComponent::GetClosestEnemy() const
{
	TArray<AActor*> PercieveActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);
	if (PercieveActors.Num() == 0)
	{
		GetCurrentlyPerceivedActors(UAISense_Damage::StaticClass(), PercieveActors);
		if (PercieveActors.Num() == 0) return nullptr;
	}

	const auto Controller = Cast<AAIController>(GetOwner());
	if (!Controller) return nullptr;

	const auto Pawn = Controller->GetPawn();
	if (!Pawn) return nullptr;

	float BestDistance = MAX_FLT;
	AActor* BestPawn = nullptr;
	for (const auto PercieveActor : PercieveActors)
	{
		const auto HealthComponent = SPUtils::GetSPPlayerComponent<USPHealthComponent>(PercieveActor);

		const auto PercievePawn = Cast<APawn>(PercieveActor);
		const auto AreEnemies = PercievePawn && SPUtils::AreEnemies(Controller, PercievePawn->Controller);

		if (HealthComponent && !HealthComponent->IsDead() && AreEnemies)
		{
			const auto CurrentDistance = (PercieveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
			if (CurrentDistance < BestDistance)
			{
				BestDistance = CurrentDistance;
				BestPawn = PercieveActor;
			}
		}
	}

	return BestPawn;
}
