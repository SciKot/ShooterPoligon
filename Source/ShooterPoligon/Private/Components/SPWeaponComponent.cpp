// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "Components/SPWeaponComponent.h"
#include "Weapon/SPBaseWeapon.h"
#include "GameFramework/Character.h"

USPWeaponComponent::USPWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USPWeaponComponent::StartFire()
{
    if (!CurrentWeapon) return;
    CurrentWeapon->StartFire();
}

void USPWeaponComponent::StopFire()
{
    if (!CurrentWeapon) return;
    CurrentWeapon->StopFire();
}

void USPWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    SpawnWeapon();
}

void USPWeaponComponent::SpawnWeapon()
{
    if (!GetWorld()) return;

    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;

    CurrentWeapon = GetWorld()->SpawnActor<ASPBaseWeapon>(WeaponClass);
    if (!CurrentWeapon) return;
    CurrentWeapon->SetOwner(Character);

    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachPointName);
}
