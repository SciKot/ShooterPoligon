// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "UI/SPGamePauseWidget.h"

#include "Components/Button.h"
#include "GameFramework/GameModeBase.h"

void USPGamePauseWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ClearPauseButton)
	{
		ClearPauseButton->OnClicked.AddDynamic(this, &USPGamePauseWidget::OnClearPause);
	}
}

void USPGamePauseWidget::OnClearPause()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->ClearPause();
}
