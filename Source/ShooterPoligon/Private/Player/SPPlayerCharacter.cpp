// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "Player/SPPlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SPWeaponComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"

ASPPlayerCharacter::ASPPlayerCharacter(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SocketOffset = FVector(0.0f, 100.0f, 80.0f);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	CameraCollisionComponent = CreateDefaultSubobject<USphereComponent>("CameraCollisionComponent");
	CameraCollisionComponent->SetupAttachment(CameraComponent);
	CameraCollisionComponent->SetSphereRadius(10.0f);
	CameraCollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	CameraCollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ASPPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASPPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASPPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ASPPlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &ASPPlayerCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASPPlayerCharacter::Jump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASPPlayerCharacter::OnRunningStart);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ASPPlayerCharacter::OnRunningStop);
	// TODO: move fire actions to weapon component?
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ASPPlayerCharacter::OnFiringStart);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ASPPlayerCharacter::OnFiringStop);
	PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &USPWeaponComponent::NextWeapon);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &USPWeaponComponent::Reload);

	DECLARE_DELEGATE_OneParam(FZoomInputSignature, bool);
	PlayerInputComponent->BindAction<FZoomInputSignature>("Zoom", IE_Pressed, WeaponComponent, &USPWeaponComponent::Zoom, true);
	PlayerInputComponent->BindAction<FZoomInputSignature>("Zoom", IE_Released, WeaponComponent, &USPWeaponComponent::Zoom, false);
}

bool ASPPlayerCharacter::isRunning() const
{
	return isRunRequested && isMovingForward && !isMovingSideways && !GetVelocity().IsZero();
}

void ASPPlayerCharacter::MoveForward(float Amount)
{
	isMovingForward = Amount > 0;
	AddMovementInput(GetActorForwardVector(), Amount);
}

void ASPPlayerCharacter::MoveRight(float Amount)
{
	isMovingSideways = FMath::Abs(Amount) > 0;
	AddMovementInput(GetActorRightVector(), Amount);
}

void ASPPlayerCharacter::OnRunningStart()
{
	isRunRequested = true;
	OnFiringStop();
}

void ASPPlayerCharacter::OnRunningStop()
{
	isRunRequested = false;
}

void ASPPlayerCharacter::OnFiringStart()
{
	if (WeaponComponent && !isRunning()) WeaponComponent->StartFire();
}

void ASPPlayerCharacter::OnFiringStop()
{
	if (!WeaponComponent) return;

	WeaponComponent->StopFire();
}

void ASPPlayerCharacter::OnCameraCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckCameraOverlap();
}

void ASPPlayerCharacter::OnCameraCollisionEndOverlap(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CheckCameraOverlap();
}

void ASPPlayerCharacter::CheckCameraOverlap()
{
	const auto HideMesh = CameraCollisionComponent->IsOverlappingComponent(GetCapsuleComponent());
	GetMesh()->SetOwnerNoSee(HideMesh);

	TArray<USceneComponent*> MeshChildren;
	GetMesh()->GetChildrenComponents(true, MeshChildren);

	for (auto MeshChild : MeshChildren)
	{
		const auto MeshChildGeometry = Cast<UPrimitiveComponent>(MeshChild);
		if (MeshChildGeometry)
		{
			MeshChildGeometry->SetOwnerNoSee(HideMesh);
		}
	}
}

void ASPPlayerCharacter::OnDeath()
{
	Super::OnDeath();

	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
}

void ASPPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(CameraCollisionComponent);

	CameraCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ASPPlayerCharacter::OnCameraCollisionBeginOverlap);
	CameraCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ASPPlayerCharacter::OnCameraCollisionEndOverlap);
}
