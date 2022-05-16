// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SPBaseCharacter.generated.h"


class UCameraComponent;
class USpringArmComponent;
class USPHealthComponent;
class UTextRenderComponent;

UCLASS()
class SHOOTERPOLIGON_API ASPBaseCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    ASPBaseCharacter(const FObjectInitializer& ObjInit);

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* SpringArmComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USPHealthComponent* HealthComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UTextRenderComponent* HealthTextComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* DeathAnimMontage;

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    UFUNCTION(BlueprintCallable, Category = "Movement")
    bool isRunning() const;

    UFUNCTION(BlueprintCallable, Category = "Movement")
    float GetMovementDirection() const;

    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
    bool isRunRequested = false;
    bool isMovingForward = false;

    void MoveForward(float Amount);
    void MoveRight(float Amount);

    void OnRunningStart();
    void OnRunningStop();

    void OnDeath();
    void OnHealthChanged(float Health);
};
