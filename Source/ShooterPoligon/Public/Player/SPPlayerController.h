// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SPCoreTypes.h"

#include "SPPlayerController.generated.h"

class USPRespawnComponent;

UCLASS()
class SHOOTERPOLIGON_API ASPPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASPPlayerController();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USPRespawnComponent* RespawnComponent;

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	void OnPauseGame();
	void OnMatchStateChanged(ESTUMatchState State);
	void OnMuteSound();
};
