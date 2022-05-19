// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SPWeaponComponent.generated.h"

class ASPBaseWeapon;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTERPOLIGON_API USPWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USPWeaponComponent();

    void StartFire();
    void StopFire();

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TSubclassOf<ASPBaseWeapon> WeaponClass;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponAttachPointName = "WeaponPoint";

    virtual void BeginPlay() override;

private:
    UPROPERTY()
    ASPBaseWeapon* CurrentWeapon = nullptr;

    void SpawnWeapon();
};
