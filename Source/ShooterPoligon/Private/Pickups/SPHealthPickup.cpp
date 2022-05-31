// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "Pickups/SPHealthPickup.h"

#include "Components/SPHealthComponent.h"
#include "SPUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All)

bool ASPHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = SPUtils::GetSPPlayerComponent<USPHealthComponent>(PlayerPawn);
	if (!HealthComponent || HealthComponent->IsDead()) return false;

	return HealthComponent->TryToAddHealth(HealAmount);
}
