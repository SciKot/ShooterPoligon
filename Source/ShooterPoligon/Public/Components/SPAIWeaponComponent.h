// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#pragma once

#include "Components/SPWeaponComponent.h"
#include "CoreMinimal.h"

#include "SPAIWeaponComponent.generated.h"

UCLASS()
class SHOOTERPOLIGON_API USPAIWeaponComponent : public USPWeaponComponent
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;
	virtual void NextWeapon() override;
};
