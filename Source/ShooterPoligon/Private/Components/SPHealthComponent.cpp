// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "Components/SPHealthComponent.h"

DEFINE_LOG_CATEGORY_STATIC(HealthComponentLog, All, All)

USPHealthComponent::USPHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USPHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    Health = MaxHealth;
    OnHealthChanged.Broadcast(Health);

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
    Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(Health);

    if (IsDead())
    {
        OnDeath.Broadcast();
    }
}
