// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "SPCoreTypes.h"

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
	void NextWeapon();
	void Reload();

	bool GetWeaponUIData(FWeaponUIData& UIData) const;
	bool GetWeaponAmmoData(FAmmoData& AmmoData) const;

	bool TryToAddAmmo(TSubclassOf<ASPBaseWeapon> WeaponType, int32 ClipsAmount);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray<FWeaponData> WeaponData;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponEquipSocketName = "WeaponPoint";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* EquipAnimMontage;

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY()
	ASPBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<ASPBaseWeapon*> SpawnedWeapons;

	UPROPERTY()
	UAnimMontage* CurrentReloadAnimMontage = nullptr;

	int32 CurrentWeaponIndex = 0;
	bool EquipAnimInProgress = false;
	bool ReloadAnimInProgress = false;

	void SpawnWeapons();
	void AttachWeaponToSocket(ASPBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
	void EquipWeapon(int32 WeaponIndex);

	void PlayAnimMontage(UAnimMontage* Animation);
	void InitAnimations();

	void OnEquipFinished(USkeletalMeshComponent* MeshComp);
	void OnReloadFinished(USkeletalMeshComponent* MeshComp);

	bool CanFire() const;
	bool CanEquip() const;
	bool CanReload() const;

	void OnEmptyClip(ASPBaseWeapon* AmmoEmptyWeapon);
	void ChangeClip();
};
