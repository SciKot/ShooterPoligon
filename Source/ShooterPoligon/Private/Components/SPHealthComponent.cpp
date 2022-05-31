// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "Components/SPHealthComponent.h"

#include "Camera/CameraShakeBase.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Pawn.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

USPHealthComponent::USPHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool USPHealthComponent::TryToAddHealth(float HealAmount)
{
	if (FMath::IsNearlyEqual(Health, MaxHealth)) return false;

	SetHealth(Health + HealAmount);
	return true;
}

void USPHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	check(MaxHealth > 0);

	SetHealth(MaxHealth);

	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USPHealthComponent::OnTakeAnyDamage);
	}
}

void USPHealthComponent::OnTakeAnyDamage(
	AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || IsDead()) return;
	SetHealth(Health - Damage);

	if (IsDead())
	{
		OnDeath.Broadcast();
	}
	else if (isAutoHeal && GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(
			AutoHealTimer, this, &USPHealthComponent::OnAutoHealTimerFired, HealTick, true, AutoHealDelay);
	}

	PlayCameraShake();
}

void USPHealthComponent::OnAutoHealTimerFired()
{
	if (Health < MaxHealth && !IsDead())
	{
		SetHealth(Health + HealPerTick);
	}
	else if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(AutoHealTimer);
	}
}

void USPHealthComponent::SetHealth(float NewHealth)
{
	const auto NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	const auto HealthDelta = NextHealth - Health;

	Health = NextHealth;
	OnHealthChanged.Broadcast(Health, HealthDelta);
}

void USPHealthComponent::PlayCameraShake()
{
	if (IsDead()) return;

	const auto Player = Cast<APawn>(GetOwner());
	if (!Player) return;

	const auto Controller = Player->GetController<APlayerController>();
	if (!Controller || !Controller->PlayerCameraManager) return;

	Controller->PlayerCameraManager->StartCameraShake(CameraShake);
}
