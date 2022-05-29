// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "Weapon/SPRifleWeapon.h"

#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Weapon/Components/SPWeaponFXComponent.h"

ASPRifleWeapon::ASPRifleWeapon()
{
	WeaponFXComponent = CreateDefaultSubobject<USPWeaponFXComponent>("WeaponFXComponent");
}

void ASPRifleWeapon::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponFXComponent);
}

void ASPRifleWeapon::StartFire()
{
	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASPRifleWeapon::MakeShot, TimeBetweenShots, true);
	MakeShot();
}

void ASPRifleWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

void ASPRifleWeapon::MakeShot()
{
	if (!GetWorld() || IsAmmoEmpty())
	{
		StopFire();
		return;
	}

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd))
	{
		StopFire();
		return;
	}

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	if (HitResult.bBlockingHit)
	{
		MakeDamage(HitResult);

		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
		// DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f);
		WeaponFXComponent->PlayImpactFX(HitResult);
	}
	else
	{
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);
	}

	DecreaseAmmo();
}

bool ASPRifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

	TraceStart = ViewLocation;
	const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
	const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;
}

void ASPRifleWeapon::MakeDamage(FHitResult& HitResult)
{
	const auto DamagedActor = HitResult.GetActor();
	if (!DamagedActor) return;

	DamagedActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this);
}