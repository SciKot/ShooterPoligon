// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "Menu/UI/SPMenuHUD.h"

#include "UI/SPBaseWidget.h"

void ASPMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MenuWidgetClass)
	{
		const auto MenuWidget = CreateWidget<USPBaseWidget>(GetWorld(), MenuWidgetClass);
		if (MenuWidget)
		{
			MenuWidget->AddToViewport();
			MenuWidget->Show();
		}
	}
}
