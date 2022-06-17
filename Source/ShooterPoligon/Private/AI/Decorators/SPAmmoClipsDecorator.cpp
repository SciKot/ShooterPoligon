// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "AI/Decorators/SPAmmoClipsDecorator.h"

#include "AIController.h"
#include "Components/SPWeaponComponent.h"
#include "SPUtils.h"

USPAmmoClipsDecorator::USPAmmoClipsDecorator()
{
	NodeName = "Ammo Clips";
}

bool USPAmmoClipsDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller) return false;

	const auto WeaponComponent = SPUtils::GetSPPlayerComponent<USPWeaponComponent>(Controller->GetPawn());
	if (!WeaponComponent || !WeaponComponent->IsAmmoNeeded(WeaponType)) return false;

	return true;
}
