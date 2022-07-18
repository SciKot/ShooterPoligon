// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "Menu/UI/SPMenuWidget.h"

#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Menu/UI/SPLevelItemWidget.h"
#include "Menu/UI/SPMenuWidget.h"
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

	InitLevelItems();
}

void USPMenuWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	if (Animation != HideAnimation) return;

	const auto SPGameInstance = GetSPGameInstance();
	if (!SPGameInstance) return;

	UGameplayStatics::OpenLevel(this, SPGameInstance->GetStartupLevel().LevelName);
}

void USPMenuWidget::InitLevelItems()
{
	const auto SPGameInstance = GetSPGameInstance();
	if (!SPGameInstance) return;

	checkf(SPGameInstance->GetLevelsData().Num() != 0, TEXT("Levels data must not be empty!"));

	if (!LevelItemsBox) return;
	LevelItemsBox->ClearChildren();

	for (auto LevelData : SPGameInstance->GetLevelsData())
	{
		const auto LevelItemWidget = CreateWidget<USPLevelItemWidget>(GetWorld(), LevelItemWidgetClass);
		if (!LevelItemWidget) continue;

		LevelItemWidget->SetLevelData(LevelData);
		LevelItemWidget->OnLevelSelected.AddUObject(this, &USPMenuWidget::OnLevelSelected);

		LevelItemsBox->AddChild(LevelItemWidget);
		LevelItemWidgets.Add(LevelItemWidget);
	}

	if (SPGameInstance->GetStartupLevel().LevelName.IsNone())
	{
		OnLevelSelected(SPGameInstance->GetLevelsData()[0]);
	}
	else
	{
		OnLevelSelected(SPGameInstance->GetStartupLevel());
	}
}

void USPMenuWidget::OnQuitGame()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

void USPMenuWidget::OnStartGame()
{
	PlayAnimation(HideAnimation);
}

void USPMenuWidget::OnLevelSelected(const FLevelData& Data)
{
	const auto SPGameInstance = GetSPGameInstance();
	if (!SPGameInstance) return;

	SPGameInstance->SetStartupLevel(Data);

	for (auto LevelItemWidget : LevelItemWidgets)
	{
		if (LevelItemWidget)
		{
			const auto IsSelected = Data.LevelName == LevelItemWidget->GetLevelData().LevelName;
			LevelItemWidget->SetSelected(IsSelected);
		}
	}
}

USPGameInstance* USPMenuWidget::GetSPGameInstance() const
{
	if (!GetWorld()) return nullptr;
	return GetWorld()->GetGameInstance<USPGameInstance>();
}
