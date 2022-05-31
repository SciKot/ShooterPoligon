// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "Weapon/SPProjectile.h"

#include "Components/SphereComponent.h"
#include "DrawdebugHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/Components/SPWeaponFXComponent.h"

ASPProjectile::ASPProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(5.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	CollisionComponent->bReturnMaterialOnMove = true;
	SetRootComponent(CollisionComponent);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
	MovementComponent->InitialSpeed = 1000.0f;
	MovementComponent->ProjectileGravityScale = 0.0f;

	WeaponFXComponent = CreateDefaultSubobject<USPWeaponFXComponent>("WeaponFXComponent");
}

void ASPProjectile::BeginPlay()
{
	Super::BeginPlay();

	check(MovementComponent);
	check(CollisionComponent);
	check(WeaponFXComponent);

	MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
	CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);	//
	CollisionComponent->OnComponentHit.AddDynamic(this, &ASPProjectile::OnProjectileHit);
	SetLifeSpan(LifeSeconds);
}

void ASPProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (!GetWorld()) return;

	MovementComponent->StopMovementImmediately();

	UGameplayStatics::ApplyRadialDamage(	//
		GetWorld(),							//
		DamageAmount,						//
		GetActorLocation(),					//
		DamageRadius,						//
		UDamageType::StaticClass(),			//
		{},									//
		this,								//
		GetController(),					//
		bDoFullDamage);

	// DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 24, FColor::Red, false, 5.0f);
	WeaponFXComponent->PlayImpactFX(Hit);
	Destroy();
}

AController* ASPProjectile::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}
