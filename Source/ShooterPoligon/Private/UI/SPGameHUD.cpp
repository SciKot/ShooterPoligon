// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "UI/SPGameHUD.h"

#include "Blueprint/UserWidget.h"
#include "Engine/Canvas.h"

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
}
