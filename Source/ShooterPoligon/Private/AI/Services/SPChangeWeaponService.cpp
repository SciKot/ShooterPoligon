// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "AI/Services/SPChangeWeaponService.h"

#include "AI/SPAIController.h"
#include "Components/SPAIWeaponComponent.h"
#include "SPUtils.h"

USPChangeWeaponService::USPChangeWeaponService()
{
	NodeName = "Change Weapon";
}

void USPChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (ChangeProbability > 0.0f && FMath::FRand() <= ChangeProbability)
	{
		const auto Controller = OwnerComp.GetAIOwner();

		if (Controller)
		{
			const auto AIWeaponComponent = SPUtils::GetSPPlayerComponent<USPAIWeaponComponent>(Controller->GetPawn());
			if (AIWeaponComponent)
			{
				AIWeaponComponent->NextWeapon();
			}
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
