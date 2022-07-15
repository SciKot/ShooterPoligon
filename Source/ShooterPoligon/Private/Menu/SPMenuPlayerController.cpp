// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "Menu/SPMenuPlayerController.h"

void ASPMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
}
