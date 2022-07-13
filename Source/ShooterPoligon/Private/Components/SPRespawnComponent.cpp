// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "Components/SPRespawnComponent.h"

#include "SPGameModeBase.h"

USPRespawnComponent::USPRespawnComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USPRespawnComponent::Respawn(int32 RespawnTime)
{
	if (!GetWorld()) return;

	RespawnCountDown = RespawnTime;
	GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &USPRespawnComponent::RespawnTimerUpdate, 1.0f, true);
}

bool USPRespawnComponent::IsRespawnInProgress() const
{
	return GetWorld() && GetWorld()->GetTimerManager().IsTimerActive(RespawnTimerHandle);
}

void USPRespawnComponent::RespawnTimerUpdate()
{
	if (--RespawnCountDown == 0)
	{
		if (!GetWorld()) return;
		GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);

		const auto GameMode = Cast<ASPGameModeBase>(GetWorld()->GetAuthGameMode());
		if (!GameMode) return;

		GameMode->RespawnRequest(Cast<AController>(GetOwner()));
	}
}
