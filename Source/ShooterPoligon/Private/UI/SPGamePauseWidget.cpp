// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "UI/SPGamePauseWidget.h"

#include "Components/Button.h"
#include "GameFramework/GameModeBase.h"

bool USPGamePauseWidget::Initialize()
{
	const auto InitStatus = Super::Initialize();

	if (ClearPauseButton)
	{
		ClearPauseButton->OnClicked.AddDynamic(this, &USPGamePauseWidget::OnClearPause);
	}

	return InitStatus;
}

void USPGamePauseWidget::OnClearPause()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->ClearPause();
}
