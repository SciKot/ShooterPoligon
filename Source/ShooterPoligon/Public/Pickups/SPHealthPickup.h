// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/SPBasePickup.h"

#include "SPHealthPickup.generated.h"

/**
 *
 */
UCLASS()
class SHOOTERPOLIGON_API ASPHealthPickup : public ASPBasePickup
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "100.0"))
	float HealAmount = 10.0f;

private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
