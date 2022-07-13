// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "UI/SPGameDataWidget.h"

#include "Player/SPPlayerState.h"
#include "SPGameModeBase.h"

int32 USPGameDataWidget::GetKillsNum() const
{
	const auto PlayerState = GetSPPlayerState();
	return PlayerState ? PlayerState->GetKillsNum() : 0;
}

int32 USPGameDataWidget::GetCurrentRoundNum() const
{
	const auto GameMode = GetSPGameMode();
	return GameMode ? GameMode->GetCurrentRoundNum() : 0;
}

int32 USPGameDataWidget::GetTotalRoundsNum() const
{
	const auto GameMode = GetSPGameMode();
	return GameMode ? GameMode->GetGameData().RoundsNum : 0;
}

int32 USPGameDataWidget::GetRoundSecondsRemaining() const
{
	const auto GameMode = GetSPGameMode();
	return GameMode ? GameMode->GetRoundSecondsRemaining() : 0;
}

ASPGameModeBase* USPGameDataWidget::GetSPGameMode() const
{
	return GetWorld() ? Cast<ASPGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}

ASPPlayerState* USPGameDataWidget::GetSPPlayerState() const
{
	return GetOwningPlayer() ? Cast<ASPPlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}
