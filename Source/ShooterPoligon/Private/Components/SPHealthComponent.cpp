// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "Components/SPHealthComponent.h"
#include "Dev/SPIceDamageType.h"
#include "Dev/SPFireDamageType.h"

DEFINE_LOG_CATEGORY_STATIC(HealthComponentLog, All, All)

USPHealthComponent::USPHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USPHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    Health = MaxHealth;

    AActor* ComponentOwner = GetOwner();
    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USPHealthComponent::OnTakeAnyDamage);
    }
}

void USPHealthComponent::OnTakeAnyDamage(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    Health -= Damage;
    UE_LOG(HealthComponentLog, Display, TEXT("Damage: %f"), Damage);

    if (DamageType)
    {
        if (DamageType->IsA<USPFireDamageType>())
        {
            UE_LOG(HealthComponentLog, Display, TEXT("High temperature detected."));
        }
        else if (DamageType->IsA<USPIceDamageType>())
        {
            UE_LOG(HealthComponentLog, Display, TEXT("Low temperature detected."));
        }
    }
}
