// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "SPGameHUD.generated.h"

/**
 *
 */
UCLASS()
class SHOOTERPOLIGON_API ASPGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

	virtual void BeginPlay() override;

private:
	void DrawCrossHair();
};
