// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "UI/SPGameHUD.h"

#include "Blueprint/UserWidget.h"
#include "Engine/Canvas.h"
#include "SPGameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogSPGameHUD, All, All);

void ASPGameHUD::DrawHUD()
{
	Super::DrawHUD();
}

void ASPGameHUD::BeginPlay()
{
	Super::BeginPlay();

	GameWidgets.Add(ESTUMatchState::InProgress, CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass));
	GameWidgets.Add(ESTUMatchState::Pause, CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass));
	GameWidgets.Add(ESTUMatchState::GameOver, CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass));

	for (auto GameWidgetPair : GameWidgets)
	{
		const auto GameWidget = GameWidgetPair.Value;
		if (!GameWidget) continue;

		GameWidget->AddToViewport();
		GameWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (GetWorld())
	{
		const auto GameMode = Cast<ASPGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &ASPGameHUD::OnMatchStateChanged);
		}
	}
}

void ASPGameHUD::OnMatchStateChanged(ESTUMatchState State)
{
	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (GameWidgets.Contains(State))
	{
		CurrentWidget = GameWidgets[State];
	}

	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
	}

	UE_LOG(LogSPGameHUD, Display, TEXT("Match state changed: %s"), *UEnum::GetValueAsString(State));
}
