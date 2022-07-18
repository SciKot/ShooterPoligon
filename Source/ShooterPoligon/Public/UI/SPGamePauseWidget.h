// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/SPBaseWidget.h"

#include "SPGamePauseWidget.generated.h"

class UButton;

UCLASS()
class SHOOTERPOLIGON_API USPGamePauseWidget : public USPBaseWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* ClearPauseButton;

	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void OnClearPause();
};
