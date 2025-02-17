// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "SPDevDamageActor.generated.h"

UCLASS()
class SHOOTERPOLIGON_API ASPDevDamageActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASPDevDamageActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radius = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool DoFullDamage = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor SphereColor = FColor::Red;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UDamageType> DamageType;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
