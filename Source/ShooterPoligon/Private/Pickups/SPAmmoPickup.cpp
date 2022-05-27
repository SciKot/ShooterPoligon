// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "Pickups/SPAmmoPickup.h"

#include "Components/SPHealthComponent.h"
#include "Components/SPWeaponComponent.h"
#include "SPUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All)

bool ASPAmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = SPUtils::GetSPPlayerComponent<USPHealthComponent>(PlayerPawn);
	if (!HealthComponent || HealthComponent->IsDead()) return false;

	const auto WeaponComponent = SPUtils::GetSPPlayerComponent<USPWeaponComponent>(PlayerPawn);
	if (!WeaponComponent) return false;

	return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
}
