// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/SPBaseWeapon.h"

#include "SPRifleWeapon.generated.h"

/**
 *
 */
UCLASS()
class SHOOTERPOLIGON_API ASPRifleWeapon : public ASPBaseWeapon
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;
	virtual void StopFire() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float TimeBetweenShots = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float BulletSpread = 0.5f;	  // Degrees

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float DamageAmount = 5.0f;

	virtual void MakeShot() override;
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

	void MakeDamage(FHitResult& HitResult);

private:
	FTimerHandle ShotTimerHandle;
};
