// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "Player/SPBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"

// Sets default values
ASPBaseCharacter::ASPBaseCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    //Attaching camera component to the root component of character (collision)
    CameraComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ASPBaseCharacter::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ASPBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASPBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &ASPBaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ASPBaseCharacter::MoveRight);
}

void ASPBaseCharacter::MoveForward (float Amount)
{
    AddMovementInput(GetActorForwardVector(), Amount);
}

void ASPBaseCharacter::MoveRight (float Amount)
{
    AddMovementInput(GetActorRightVector(), Amount);
}
