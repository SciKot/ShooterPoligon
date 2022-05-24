// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"

#include "SPPlayerHUDWidget.generated.h"

/**
 *
 */
UCLASS()
class SHOOTERPOLIGON_API USPPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetHealthPercent() const;
};
