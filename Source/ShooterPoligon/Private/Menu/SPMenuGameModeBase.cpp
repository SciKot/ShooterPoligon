// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "Menu/SPMenuGameModeBase.h"

#include "Menu/SPMenuPlayerController.h"
#include "Menu/UI/SPMenuHUD.h"

ASPMenuGameModeBase::ASPMenuGameModeBase()
{
	PlayerControllerClass = ASPMenuPlayerController::StaticClass();
	HUDClass = ASPMenuHUD::StaticClass();
}
