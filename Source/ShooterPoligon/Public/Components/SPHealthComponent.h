// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "SPCoreTypes.h"

#include "SPHealthComponent.generated.h"

class UCameraShakeBase;
class UPhysicalMaterial;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTERPOLIGON_API USPHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USPHealthComponent();

	FOnDeathSignature OnDeath;
	FOnHealthChangedSignature OnHealthChanged;

	UFUNCTION(BlueprintCallable)
	bool IsDead() { return FMath::IsNearlyZero(Health); }

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealthPercent() const { return Health / MaxHealth; }

	float GetHealth() const { return Health; }

	bool TryToAddHealth(float HealAmount);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = 0.0f, ClampMax = 10000.0f))
	float MaxHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AutoHeal")
	bool isAutoHeal = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AutoHeal", meta = (ClampMin = 0.0f, EditCondition = "isAutoHeal"))
	float AutoHealDelay = 3.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AutoHeal", meta = (ClampMin = 0.0f, EditCondition = "isAutoHeal"))
	float HealTick = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AutoHeal",
		meta = (ClampMin = 0.0f, ClampMax = 10000.0f, EditCondition = "isAutoHeal"))
	float HealPerTick = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	TSubclassOf<UCameraShakeBase> CameraShake;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	TMap<UPhysicalMaterial*, float> DamageModifiers;

	virtual void BeginPlay() override;

private:
	float Health = 0.0f;
	FTimerHandle AutoHealTimer;

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy,
		AActor* DamageCauser);

	UFUNCTION()
	void OnTakePointDamage(AActor* DamagedActor, float Damage, class AController* InstigatedBy, FVector HitLocation,
		class UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const class UDamageType* DamageType,
		AActor* DamageCauser);

	UFUNCTION()
	void OnTakeRadialDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, FVector Origin,
		FHitResult HitInfo, class AController* InstigatedBy, AActor* DamageCauser);

	void SetHealth(float Value);
	void OnAutoHealTimerFired();
	void PlayCameraShake();

	void Killed(AController* KillerController);
	void ApplyDamage(float Damage, AController* InstigatedBy);
	float GetPointDamageModifier(AActor* DamagedActor, const FName& BoneName);
};
