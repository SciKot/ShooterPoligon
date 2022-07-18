// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SPCoreTypes.h"
#include "UI/SPBaseWidget.h"

#include "SPMenuWidget.generated.h"

class UButton;
class UHorizontalBox;
class USPGameInstance;
class USPLevelItemWidget;

UCLASS()
class SHOOTERPOLIGON_API USPMenuWidget : public USPBaseWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* StartGameButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitGameButton;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* LevelItemsBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> LevelItemWidgetClass;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* HideAnimation;

	virtual void NativeOnInitialized() override;
	virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;

private:
	UPROPERTY()
	TArray<USPLevelItemWidget*> LevelItemWidgets;

	UFUNCTION()
	void OnStartGame();

	UFUNCTION()
	void OnQuitGame();

	void InitLevelItems();
	void OnLevelSelected(const FLevelData& Data);
	USPGameInstance* GetSPGameInstance() const;
};
