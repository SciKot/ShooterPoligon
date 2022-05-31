// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "Player/SPBaseCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SPCharacterMovementComponent.h"
#include "Components/SPHealthComponent.h"
#include "Components/SPWeaponComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseCharacter, All, All)

ASPBaseCharacter::ASPBaseCharacter(const FObjectInitializer& ObjInit)
	: Super(ObjInit.SetDefaultSubobjectClass<USPCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	// Attaching spring arm component to the root component of character (collision)
	SpringArmComponent->SetupAttachment(GetRootComponent());
	// To allow character to look up and down
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SocketOffset = FVector(0.0f, 100.0f, 80.0f);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	HealthComponent = CreateDefaultSubobject<USPHealthComponent>("HealthComponent");

	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
	HealthTextComponent->SetupAttachment(GetRootComponent());
	HealthTextComponent->SetOwnerNoSee(true);

	WeaponComponent = CreateDefaultSubobject<USPWeaponComponent>("WeaponComponent");
}

void ASPBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent);
	check(HealthTextComponent);
	check(GetCharacterMovement());
	check(GetMesh());

	OnHealthChanged(HealthComponent->GetHealth(), 0.0f);
	HealthComponent->OnDeath.AddUObject(this, &ASPBaseCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &ASPBaseCharacter::OnHealthChanged);

	LandedDelegate.AddDynamic(this, &ASPBaseCharacter::OnGroundLanded);
}

void ASPBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASPBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASPBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASPBaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ASPBaseCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &ASPBaseCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASPBaseCharacter::Jump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASPBaseCharacter::OnRunningStart);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ASPBaseCharacter::OnRunningStop);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ASPBaseCharacter::OnFiringStart);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ASPBaseCharacter::OnFiringStop);
	PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &USPWeaponComponent::NextWeapon);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &USPWeaponComponent::Reload);
}

bool ASPBaseCharacter::isRunning() const
{
	return isRunRequested && isMovingForward && !isMovingSideways && !GetVelocity().IsZero();
}

float ASPBaseCharacter::GetMovementDirection() const
{
	if (GetVelocity().IsZero()) return 0.0f;
	const auto NormalizedVelocityVector = GetVelocity().GetSafeNormal();
	const auto AngleBetween =
		FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(GetActorForwardVector(), NormalizedVelocityVector)));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), NormalizedVelocityVector);
	return CrossProduct.IsZero() ? AngleBetween : AngleBetween * FMath::Sign(CrossProduct.Z);
}

void ASPBaseCharacter::MoveForward(float Amount)
{
	isMovingForward = Amount > 0;
	AddMovementInput(GetActorForwardVector(), Amount);
}

void ASPBaseCharacter::MoveRight(float Amount)
{
	isMovingSideways = FMath::Abs(Amount) > 0;
	AddMovementInput(GetActorRightVector(), Amount);
}

void ASPBaseCharacter::OnRunningStart()
{
	isRunRequested = true;
	OnFiringStop();
}

void ASPBaseCharacter::OnRunningStop()
{
	isRunRequested = false;
}

void ASPBaseCharacter::OnFiringStart()
{
	if (WeaponComponent && !isRunning()) WeaponComponent->StartFire();
}

void ASPBaseCharacter::OnFiringStop()
{
	if (!WeaponComponent) return;

	WeaponComponent->StopFire();
}

void ASPBaseCharacter::OnDeath()
{
	UE_LOG(LogBaseCharacter, Display, TEXT("Player %s is dead"), *GetName());

	// PlayAnimMontage(DeathAnimMontage);

	GetCharacterMovement()->DisableMovement();

	SetLifeSpan(LifeSpanOnDeath);
	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}

	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	WeaponComponent->StopFire();

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
}

void ASPBaseCharacter::OnHealthChanged(float Health, float HealthDelta)
{
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT(" % .0f"), Health)));
}

void ASPBaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
	const auto FallVelocityZ = -GetVelocity().Z;
	UE_LOG(LogBaseCharacter, Display, TEXT("Fall Velocity Z: %f"), FallVelocityZ);

	if (FallVelocityZ < LandedDamageVelocity.X) return;

	const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
	UE_LOG(LogBaseCharacter, Display, TEXT("Final damage: %f"), FinalDamage);
	TakeDamage(FinalDamage, FDamageEvent(), nullptr, nullptr);
}

// Note,characters turns with help of controller function.
// This can help in separating character rotation and camera rotation.
