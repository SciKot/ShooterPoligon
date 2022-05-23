// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "SPProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class SHOOTERPOLIGON_API ASPProjectile : public AActor
{
	GENERATED_BODY()

public:
	ASPProjectile();

	void SetShotDirection(const FVector Direction) { ShotDirection = Direction; }

protected:
	UPROPERTY(VisibleAnywhere, Category = "Weapon");
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = "Weapon");
	UProjectileMovementComponent* MovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon");
	float DamageRadius = 200.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon");
	float DamageAmount = 70.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon");
	bool bDoFullDamage = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon");
	float LifeSeconds = 5.0f;

	virtual void BeginPlay() override;

private:
	FVector ShotDirection;

	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit);

	AController* GetController() const;
};
