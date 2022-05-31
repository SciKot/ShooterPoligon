// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/SPBaseCharacter.h"

#include "SPAICharacter.generated.h"

class UBehaviorTree;

UCLASS()
class SHOOTERPOLIGON_API ASPAICharacter : public ASPBaseCharacter
{
	GENERATED_BODY()

public:
	ASPAICharacter(const FObjectInitializer& ObjInit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;
};
