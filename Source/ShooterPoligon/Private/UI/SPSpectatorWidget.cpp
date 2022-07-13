// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "UI/SPSpectatorWidget.h"

#include "Components/SPRespawnComponent.h"
#include "SPUtils.h"

bool USPSpectatorWidget::GetRespawnTime(int32& CountDownTime) const
{
	const auto RespawnComponent = SPUtils::GetSPPlayerComponent<USPRespawnComponent>(GetOwningPlayer());
	if (!RespawnComponent || !RespawnComponent->IsRespawnInProgress()) return false;

	CountDownTime = RespawnComponent->GetRespawnCountDown();
	return true;
}
