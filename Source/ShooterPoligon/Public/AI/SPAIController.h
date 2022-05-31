// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#pragma once

#include "AIController.h"
#include "CoreMinimal.h"

#include "SPAIController.generated.h"

UCLASS()
class SHOOTERPOLIGON_API ASPAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void OnPossess(APawn* InPawn) override;
};
