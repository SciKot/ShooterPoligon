// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "SPCoreTypes.h"

#include "SPWeaponFXComponent.generated.h"

class UNiagaraSystem;
class UPhysicalMaterial;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTERPOLIGON_API USPWeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USPWeaponFXComponent();

	void PlayImpactFX(const FHitResult& Hit);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	FImpactData DefaultImpactData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	TMap<UPhysicalMaterial*, FImpactData> ImpactDataMap;
};
