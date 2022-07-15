// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "Menu/UI/SPMenuWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SPGameInstance.h"

DEFINE_LOG_CATEGORY_STATIC(LogSPMenuWidget, All, All);

void USPMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &USPMenuWidget::OnStartGame);
	}

	if (QuitGameButton)
	{
		QuitGameButton->OnClicked.AddDynamic(this, &USPMenuWidget::OnQuitGame);
	}
}

void USPMenuWidget::OnStartGame()
{
	if (!GetWorld()) return;

	const auto STUGameInstance = GetWorld()->GetGameInstance<USPGameInstance>();
	if (!STUGameInstance) return;

	if (STUGameInstance->GetStartupLevelName().IsNone())
	{
		UE_LOG(LogSPMenuWidget, Error, TEXT("Level name is NONE"));
		return;
	}

	UGameplayStatics::OpenLevel(this, STUGameInstance->GetStartupLevelName());
}

void USPMenuWidget::OnQuitGame()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
