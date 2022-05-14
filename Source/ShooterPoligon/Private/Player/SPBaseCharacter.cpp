// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "Player/SPBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ASPBaseCharacter::ASPBaseCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
    // Attaching spring arm component to the root component of character (collision)
    SpringArmComponent->SetupAttachment(GetRootComponent());
    //To allow char to look up and down
    SpringArmComponent->bUsePawnControlRotation = true;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);
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
    PlayerInputComponent->BindAxis("LookUp", this, &ASPBaseCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &ASPBaseCharacter::AddControllerYawInput);
}

void ASPBaseCharacter::MoveForward(float Amount)
{
    AddMovementInput(GetActorForwardVector(), Amount);
}

void ASPBaseCharacter::MoveRight(float Amount)
{
    AddMovementInput(GetActorRightVector(), Amount);
}

//Note,characters turns with help of controller function.
//This can help in separating character rotation and camera rotation.
