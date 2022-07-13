// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "Player/SPPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogSPPlayerState, All, All);

void ASPPlayerState::LogInfo()
{
	UE_LOG(LogSPPlayerState, Display, TEXT("TeamID: %i, Kills: %i, Deaths: %i"), TeamID, KillsNum, DeathsNum);
}
