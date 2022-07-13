// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "Player/SPPlayerController.h"
#include "Components/SPRespawnComponent.h"

ASPPlayerController::ASPPlayerController()
{
	RespawnComponent = CreateDefaultSubobject<USPRespawnComponent>("RespawnComponent");
}
