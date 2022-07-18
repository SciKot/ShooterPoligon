// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SPCoreTypes.h"
#include "UI/SPBaseWidget.h"

#include "SPGameOverWidget.generated.h"

class UVerticalBox;
class UButton;

UCLASS()
class SHOOTERPOLIGON_API USPGameOverWidget : public USPBaseWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* PlayerStatBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;

	UPROPERTY(meta = (BindWidget))
	UButton* ResetLevelButton;

	virtual void NativeOnInitialized() override;

private:
	void OnMatchStateChanged(ESTUMatchState State);
	void UpdatePlayersStat();

	UFUNCTION()
	void OnResetLevel();
};
