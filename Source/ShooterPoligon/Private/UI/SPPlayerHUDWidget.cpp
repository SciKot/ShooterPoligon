// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "UI/SPPlayerHUDWidget.h"

#include "Components/ProgressBar.h"
#include "Components/SPHealthComponent.h"
#include "Components/SPWeaponComponent.h"
#include "Player/SPPlayerState.h"
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

int32 USPPlayerHUDWidget::GetKillsNum() const
{
	const auto Controller = GetOwningPlayer();
	if (!Controller) return 0;

	const auto PlayerState = Cast<ASPPlayerState>(Controller->PlayerState);
	return PlayerState ? PlayerState->GetKillsNum() : 0;
}

FString USPPlayerHUDWidget::FormatBullets(int32 BulletsNum) const
{
	const int32 MaxLen = 3;
	const TCHAR PrefixSymbol = '0';

	auto BulletStr = FString::FromInt(BulletsNum);
	const auto SymbolsNumToAdd = MaxLen - BulletStr.Len();

	if (SymbolsNumToAdd > 0)
	{
		BulletStr = FString::ChrN(SymbolsNumToAdd, PrefixSymbol).Append(BulletStr);
	}

	return BulletStr;
}

void USPPlayerHUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (GetOwningPlayer())
	{
		GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &USPPlayerHUDWidget::OnNewPawn);
		OnNewPawn(GetOwningPlayerPawn());
	}
}

void USPPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta)
{
	if (HealthDelta < 0.0f)
	{
		OnTakeDamage();
	}
	UpdateHealthBar();
}

void USPPlayerHUDWidget::OnNewPawn(APawn* NewPawn)
{
	const auto HealthComponent = SPUtils::GetSPPlayerComponent<USPHealthComponent>(NewPawn);
	if (HealthComponent && !HealthComponent->OnHealthChanged.IsBoundToObject(this))
	{
		HealthComponent->OnHealthChanged.AddUObject(this, &USPPlayerHUDWidget::OnHealthChanged);
	}
	UpdateHealthBar();
}

void USPPlayerHUDWidget::UpdateHealthBar()
{
	if (HealthProgressBar)
	{
		HealthProgressBar->SetFillColorAndOpacity(GetHealthPercent() > PercentColorThreshold ? GoodColor : BadColor);
	}
}
