// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "AI/Decorators/SPHealthPercentDecorator.h"

#include "AIController.h"
#include "Components/SPHealthComponent.h"
#include "SPUtils.h"

USPHealthPercentDecorator::USPHealthPercentDecorator()
{
	NodeName = "Health Percent";
}

bool USPHealthPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller) return false;

	const auto HealthComponent = SPUtils::GetSPPlayerComponent<USPHealthComponent>(Controller->GetPawn());
	if (!HealthComponent || HealthComponent->IsDead()) return false;

	return HealthComponent->GetHealthPercent() <= HealthPercent;
}
