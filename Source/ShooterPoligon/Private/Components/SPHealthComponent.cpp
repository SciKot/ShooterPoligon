// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "Components/SPHealthComponent.h"

#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

USPHealthComponent::USPHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
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

void USPHealthComponent::SetHealth(float Value)
{
	Health = FMath::Clamp(Value, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(Health);
}
