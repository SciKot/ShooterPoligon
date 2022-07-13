// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "UI/SPPlayerHUDWidget.h"

#include "Components/SPHealthComponent.h"
#include "Components/SPWeaponComponent.h"
#include "SPUtils.h"

float USPPlayerHUDWidget::GetHealthPercent() const
{
	const auto HealthComponent = SPUtils::GetSPPlayerComponent<USPHealthComponent>(GetOwningPlayerPawn());
	if (!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();
}

bool USPPlayerHUDWidget::GetWeaponUIData(FWeaponUIData& UIData) const
{
	const auto WeaponComponent = SPUtils::GetSPPlayerComponent<USPWeaponComponent>(GetOwningPlayerPawn());
	if (!WeaponComponent) return false;

	return WeaponComponent->GetWeaponUIData(UIData);
}

bool USPPlayerHUDWidget::GetWeaponAmmoData(FAmmoData& AmmoData) const
{
	const auto WeaponComponent = SPUtils::GetSPPlayerComponent<USPWeaponComponent>(GetOwningPlayerPawn());
	if (!WeaponComponent) return false;

	return WeaponComponent->GetWeaponAmmoData(AmmoData);
}

bool USPPlayerHUDWidget::IsPlayerAlive() const
{
	const auto HealthComponent = SPUtils::GetSPPlayerComponent<USPHealthComponent>(GetOwningPlayerPawn());
	return HealthComponent && !HealthComponent->IsDead();
}

bool USPPlayerHUDWidget::IsPlayerSpecteting() const
{
	const auto Controller = GetOwningPlayer();
	return Controller && Controller->GetStateName() == NAME_Spectating;
}

bool USPPlayerHUDWidget::Initialize()
{
	if (GetOwningPlayer())
	{
		GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &USPPlayerHUDWidget::OnNewPawn);
		OnNewPawn(GetOwningPlayerPawn());
	}

	return Super::Initialize();
}

void USPPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta)
{
	if (HealthDelta < 0.0f)
	{
		OnTakeDamage();
	}
}

void USPPlayerHUDWidget::OnNewPawn(APawn* NewPawn)
{
	const auto HealthComponent = SPUtils::GetSPPlayerComponent<USPHealthComponent>(NewPawn);
	if (HealthComponent && !HealthComponent->OnHealthChanged.IsBoundToObject(this))
	{
		HealthComponent->OnHealthChanged.AddUObject(this, &USPPlayerHUDWidget::OnHealthChanged);
	}
}
