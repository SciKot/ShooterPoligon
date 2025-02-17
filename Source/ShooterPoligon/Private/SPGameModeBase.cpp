// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "SPGameModeBase.h"

#include "AIController.h"
#include "Components/SPRespawnComponent.h"
#include "Components/SPWeaponComponent.h"
#include "EngineUtils.h"
#include "Player/SPBaseCharacter.h"
#include "Player/SPPlayerController.h"
#include "Player/SPPlayerState.h"
#include "SPUtils.h"
#include "UI/SPGameHUD.h"

DEFINE_LOG_CATEGORY_STATIC(LogSPGameModeBase, All, All);

ASPGameModeBase::ASPGameModeBase()
{
	DefaultPawnClass = ASPBaseCharacter::StaticClass();
	PlayerControllerClass = ASPPlayerController::StaticClass();
	HUDClass = ASPGameHUD::StaticClass();
	PlayerStateClass = ASPPlayerState::StaticClass();
}

void ASPGameModeBase::StartPlay()
{
	Super::StartPlay();

	SpawnBots();
	CreateTeamsInfo();

	CurrentRound = 1;
	StartRound();

	SetMatchState(ESTUMatchState::InProgress);
}

UClass* ASPGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (InController && InController->IsA<AAIController>())
	{
		return AIPawnClass;
	}
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void ASPGameModeBase::Killed(AController* KillerController, AController* VictimController)
{
	const auto KillerPlayerState = KillerController ? Cast<ASPPlayerState>(KillerController->PlayerState) : nullptr;
	const auto VictimPlayerState = VictimController ? Cast<ASPPlayerState>(VictimController->PlayerState) : nullptr;

	if (KillerPlayerState)
	{
		KillerPlayerState->AddKill();
	}

	if (VictimPlayerState)
	{
		VictimPlayerState->AddDeath();
	}

	StartRespawn(VictimController);
}

void ASPGameModeBase::RespawnRequest(AController* Controller)
{
	ResetOnePlayer(Controller);
}

bool ASPGameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
	const auto PauseSet = Super::SetPause(PC, CanUnpauseDelegate);
	if (PauseSet)
	{
		StopAllFire();
		SetMatchState(ESTUMatchState::Pause);
	}
	return PauseSet;
}

bool ASPGameModeBase::ClearPause()
{
	const auto PauseCleared = Super::ClearPause();
	if (PauseCleared)
	{
		SetMatchState(ESTUMatchState::InProgress);
	}
	return PauseCleared;
}

void ASPGameModeBase::SpawnBots()
{
	if (!GetWorld()) return;

	for (int32 i = 0; i < GameData.PlayersNum - 1; ++i)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const auto SPAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
		RestartPlayer(SPAIController);
	}
}

void ASPGameModeBase::StartRound()
{
	RoundCountDown = GameData.RoundTime;
	GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &ASPGameModeBase::GameTimerUpdate, 1.0f, true);
}

void ASPGameModeBase::GameTimerUpdate()
{
	// UE_LOG(LogSPGameModeBase, Display, TEXT("Time: %i / Round: %i/%i"), RoundCountDown, CurrentRound, GameData.RoundsNum);

	if (--RoundCountDown == 0)
	{
		GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);

		if (CurrentRound + 1 <= GameData.RoundsNum)
		{
			++CurrentRound;
			ResetPlayers();
			StartRound();
		}
		else
		{
			GameOver();
		}
	}
}

void ASPGameModeBase::ResetPlayers()
{
	if (!GetWorld()) return;

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		ResetOnePlayer(It->Get());
	}
}

void ASPGameModeBase::ResetOnePlayer(AController* Controller)
{
	if (Controller && Controller->GetPawn())
	{
		Controller->GetPawn()->Reset();
	}
	RestartPlayer(Controller);
	SetPlayerColor(Controller);
}

void ASPGameModeBase::CreateTeamsInfo()
{
	if (!GetWorld()) return;

	int32 TeamID = 1;
	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller) continue;

		const auto PlayerState = Cast<ASPPlayerState>(Controller->PlayerState);
		if (!PlayerState) continue;

		PlayerState->SetTeamID(TeamID);
		PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));
		PlayerState->SetPlayerName(Controller->IsPlayerController() ? "Player" : "Bot");
		SetPlayerColor(Controller);

		TeamID = TeamID % GameData.TeamsNum + 1;
	}
}

FLinearColor ASPGameModeBase::DetermineColorByTeamID(int32 TeamID) const
{
	if (TeamID - 1 < GameData.TeamColors.Num())
	{
		return GameData.TeamColors[TeamID - 1];
	}
	UE_LOG(LogSPGameModeBase, Warning, TEXT("No color for team id: %i, set to default: %s"), TeamID,
		*GameData.DefaultTeamColor.ToString());
	return GameData.DefaultTeamColor;
}

void ASPGameModeBase::SetPlayerColor(AController* Controller)
{
	if (!Controller) return;

	const auto Character = Cast<ASPBaseCharacter>(Controller->GetPawn());
	if (!Character) return;

	const auto PlayerState = Cast<ASPPlayerState>(Controller->PlayerState);
	if (!PlayerState) return;

	Character->SetPlayerColor(PlayerState->GetTeamColor());
}

void ASPGameModeBase::LogPlayerInfo()
{
	if (!GetWorld()) return;

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller) continue;

		const auto PlayerState = Cast<ASPPlayerState>(Controller->PlayerState);
		if (!PlayerState) continue;

		PlayerState->LogInfo();
	}
}

void ASPGameModeBase::StartRespawn(AController* Controller)
{
	const auto RespawnAvailable = RoundCountDown > GameData.MinRoundTimeForRespawn + GameData.RespawnTime;
	if (!RespawnAvailable) return;

	const auto RespawnComponent = SPUtils::GetSPPlayerComponent<USPRespawnComponent>(Controller);
	if (!RespawnComponent) return;

	RespawnComponent->Respawn(GameData.RespawnTime);
}

void ASPGameModeBase::GameOver()
{
	UE_LOG(LogSPGameModeBase, Display, TEXT("======== GAME OVER ========"));
	LogPlayerInfo();

	for (auto Pawn : TActorRange<APawn>(GetWorld()))
	{
		if (Pawn)
		{
			Pawn->TurnOff();
			Pawn->DisableInput(nullptr);
		}
	}

	SetMatchState(ESTUMatchState::GameOver);
}

void ASPGameModeBase::SetMatchState(ESTUMatchState State)
{
	if (MatchState == State) return;

	MatchState = State;
	OnMatchStateChanged.Broadcast(MatchState);
}

void ASPGameModeBase::StopAllFire()
{
	for (auto Pawn : TActorRange<APawn>(GetWorld()))
	{
		const auto WeaponComponent = SPUtils::GetSPPlayerComponent<USPWeaponComponent>(Pawn);
		if (!WeaponComponent) continue;

		WeaponComponent->Zoom(false);
		WeaponComponent->StopFire();
	}
}
