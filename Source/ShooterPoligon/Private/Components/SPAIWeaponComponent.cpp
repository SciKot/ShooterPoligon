// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "Components/SPAIWeaponComponent.h"

#include "Weapon/SPBaseWeapon.h"

void USPAIWeaponComponent::StartFire()
{
	if (!CanFire()) return;

	if (CurrentWeapon->IsAmmoEmpty())
	{
		NextWeapon();
	}
	else
	{
		CurrentWeapon->StartFire();
	}
}

void USPAIWeaponComponent::NextWeapon()
{
	if (!CanEquip()) return;

	int32 NextIndex = (CurrentWeaponIndex + 1) % SpawnedWeapons.Num();
	while (NextIndex != CurrentWeaponIndex)
	{
		if (!SpawnedWeapons[NextIndex]->IsAmmoEmpty()) break;
		NextIndex = (NextIndex + 1) % SpawnedWeapons.Num();
	}

	if (CurrentWeaponIndex != NextIndex)
	{
		CurrentWeaponIndex = NextIndex;
		EquipWeapon(CurrentWeaponIndex);
	}
}
