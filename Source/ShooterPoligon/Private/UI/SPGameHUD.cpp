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
	auto PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);
	if (PlayerHUDWidget)
	{
		PlayerHUDWidget->AddToViewport();
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
	UE_LOG(LogSPGameHUD, Display, TEXT("Match state changed: %s"), *UEnum::GetValueAsString(State));
}
