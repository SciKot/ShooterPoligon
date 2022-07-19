// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "Player/SPPlayerController.h"

#include "Components/SPRespawnComponent.h"
#include "SPGameInstance.h"
#include "SPGameModeBase.h"

ASPPlayerController::ASPPlayerController()
{
	RespawnComponent = CreateDefaultSubobject<USPRespawnComponent>("RespawnComponent");
}

void ASPPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		const auto GameMode = Cast<ASPGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &ASPPlayerController::OnMatchStateChanged);
		}
	}
}

void ASPPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (!InputComponent) return;

	InputComponent->BindAction("PauseGame", IE_Pressed, this, &ASPPlayerController::OnPauseGame);
	InputComponent->BindAction("Mute", IE_Pressed, this, &ASPPlayerController::OnMuteSound);
}

void ASPPlayerController::OnPauseGame()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->SetPause(this);
}

void ASPPlayerController::OnMatchStateChanged(ESTUMatchState State)
{
	if (State == ESTUMatchState::InProgress)
	{
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
	else
	{
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
	}
}

void ASPPlayerController::OnMuteSound()
{
	if (!GetWorld()) return;

	const auto STUGameInstace = GetWorld()->GetGameInstance<USPGameInstance>();
	if (!STUGameInstace) return;

	STUGameInstace->ToggleVolume();
}
