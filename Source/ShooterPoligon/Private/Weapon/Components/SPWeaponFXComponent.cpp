// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "Weapon/Components/SPWeaponFXComponent.h"

#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

USPWeaponFXComponent::USPWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USPWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
	auto ImpactData = DefaultImpactData;

	if (Hit.PhysMaterial.IsValid())
	{
		const auto PhysMat = Hit.PhysMaterial.Get();
		if (ImpactDataMap.Contains(PhysMat))
		{
			ImpactData = ImpactDataMap[PhysMat];
		}
	}

	// niagara
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),	  //
		ImpactData.NiagaraEffect,								  //
		Hit.ImpactPoint,										  //
		Hit.ImpactNormal.Rotation());

	// decal
	auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(GetWorld(),	//
		ImpactData.DecalData.Material,											//
		ImpactData.DecalData.Size,												//
		Hit.ImpactPoint,														//
		(Hit.ImpactNormal * -1.0f).Rotation());
	if (DecalComponent)
	{
		DecalComponent->SetFadeOut(ImpactData.DecalData.LifeTime, ImpactData.DecalData.FadeOutTime);
	}
}
