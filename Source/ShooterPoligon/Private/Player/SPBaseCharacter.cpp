// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "Player/SPBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SPCharacterMovementComponent.h"
#include "Components/SPHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All)

// Sets default values
ASPBaseCharacter::ASPBaseCharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<USPCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
    // Attaching spring arm component to the root component of character (collision)
    SpringArmComponent->SetupAttachment(GetRootComponent());
    // To allow character to look up and down
    SpringArmComponent->bUsePawnControlRotation = true;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);

    HealthComponent = CreateDefaultSubobject<USPHealthComponent>("HealthComponent");

    HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
    HealthTextComponent->SetupAttachment(GetRootComponent());
}

bool ASPBaseCharacter::isRunning() const
{
    return isRunRequested && isMovingForward && !GetVelocity().IsZero();
}

float ASPBaseCharacter::GetMovementDirection() const
{
    if (GetVelocity().IsZero()) return 0.0f;
    const auto NormalizedVelocityVector = GetVelocity().GetSafeNormal();
    const auto AngleBetween = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(GetActorForwardVector(), NormalizedVelocityVector)));
    const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), NormalizedVelocityVector);
    return CrossProduct.IsZero() ? AngleBetween : AngleBetween * FMath::Sign(CrossProduct.Z);
}

// Called when the game starts or when spawned
void ASPBaseCharacter::BeginPlay()
{
    Super::BeginPlay();

    check(HealthComponent);
    check(HealthTextComponent);
    check(GetCharacterMovement());

    OnHealthChanged(HealthComponent->GetHealth());
    HealthComponent->OnDeath.AddUObject(this, &ASPBaseCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &ASPBaseCharacter::OnHealthChanged);
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
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASPBaseCharacter::Jump);
    PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASPBaseCharacter::OnRunningStart);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &ASPBaseCharacter::OnRunningStop);
}

void ASPBaseCharacter::MoveForward(float Amount)
{
    isMovingForward = Amount > 0;
    AddMovementInput(GetActorForwardVector(), Amount);
}

void ASPBaseCharacter::MoveRight(float Amount)
{
    AddMovementInput(GetActorRightVector(), Amount);
}

void ASPBaseCharacter::OnRunningStart ()
{
    isRunRequested = true;
}

void ASPBaseCharacter::OnRunningStop ()
{
    isRunRequested = false;
}

void ASPBaseCharacter::OnDeath ()
{
    UE_LOG(BaseCharacterLog, Display, TEXT("Player %s is dead"), *GetName());

    PlayAnimMontage(DeathAnimMontage);

    GetCharacterMovement()->DisableMovement();

    SetLifeSpan(5.0f);
    if (Controller)
    {
        Controller->ChangeState(NAME_Spectating);
    }
}

void ASPBaseCharacter::OnHealthChanged(float Health)
{
    HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT(" % .0f"), Health)));
}

// Note,characters turns with help of controller function.
// This can help in separating character rotation and camera rotation.
