// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "UI/SPGoToMenuWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "SPGameInstance.h"

DEFINE_LOG_CATEGORY_STATIC(LogSPGoToMenuWidget, All, All);

void USPGoToMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (MainMenuButton)
	{
		MainMenuButton->OnClicked.AddDynamic(this, &USPGoToMenuWidget::OnGoToMainMenu);
	}
}

void USPGoToMenuWidget::OnGoToMainMenu()
{
	if (!GetWorld()) return;

	const auto STUGameInstance = GetWorld()->GetGameInstance<USPGameInstance>();
	if (!STUGameInstance) return;

	if (STUGameInstance->GetMainMenuLevelName().IsNone())
	{
		UE_LOG(LogSPGoToMenuWidget, Error, TEXT("Main menu level name is NONE"));
		return;
	}

	UGameplayStatics::OpenLevel(this, STUGameInstance->GetMainMenuLevelName());
}
