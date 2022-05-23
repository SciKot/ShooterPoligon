// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/SPBaseWeapon.h"

#include "SPLauncherWeapon.generated.h"

class ASPProjectile;

UCLASS()
class SHOOTERPOLIGON_API ASPLauncherWeapon : public ASPBaseWeapon
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<ASPProjectile> ProjectileClass;

	virtual void MakeShot() override;
};
