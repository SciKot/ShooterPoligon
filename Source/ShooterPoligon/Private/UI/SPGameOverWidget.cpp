// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "UI/SPGameOverWidget.h"

#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"
#include "Player/SPPlayerState.h"
#include "SPGameModeBase.h"
#include "SPUtils.h"
#include "UI/SPPlayerStatRowWidget.h"

void USPGameOverWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (GetWorld())
	{
		const auto GameMode = Cast<ASPGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &USPGameOverWidget::OnMatchStateChanged);
		}
	}

	if (ResetLevelButton)
	{
		ResetLevelButton->OnClicked.AddDynamic(this, &USPGameOverWidget::OnResetLevel);
	}
}

void USPGameOverWidget::OnMatchStateChanged(ESTUMatchState State)
{
	if (State == ESTUMatchState::GameOver)
	{
		UpdatePlayersStat();
	}
}

void USPGameOverWidget::UpdatePlayersStat()
{
	if (!GetWorld() || !PlayerStatBox) return;

	PlayerStatBox->ClearChildren();

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller) continue;

		const auto PlayerState = Cast<ASPPlayerState>(Controller->PlayerState);
		if (!PlayerState) continue;

		const auto PlayerStatRowWidget = CreateWidget<USPPlayerStatRowWidget>(GetWorld(), PlayerStatRowWidgetClass);
		if (!PlayerStatRowWidget) continue;

		PlayerStatRowWidget->SetPlayerName(FText::FromString(PlayerState->GetPlayerName()));
		PlayerStatRowWidget->SetKills(SPUtils::TextFromInt(PlayerState->GetKillsNum()));
		PlayerStatRowWidget->SetDeaths(SPUtils::TextFromInt(PlayerState->GetDeathsNum()));
		PlayerStatRowWidget->SetTeam(SPUtils::TextFromInt(PlayerState->GetTeamID()));
		PlayerStatRowWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());
		PlayerStatRowWidget->SetTeamColor(PlayerState->GetTeamColor());

		PlayerStatBox->AddChild(PlayerStatRowWidget);
	}
}

void USPGameOverWidget::OnResetLevel()
{
	const auto CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
	UGameplayStatics::OpenLevel(this, FName(CurrentLevelName));
}
