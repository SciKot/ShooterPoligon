// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "SPCoreTypes.h"

#include "SPGameOverWidget.generated.h"

class UVerticalBox;

UCLASS()
class SHOOTERPOLIGON_API USPGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

protected:
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* PlayerStatBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;

private:
	void OnMatchStateChanged(ESTUMatchState State);
	void UpdatePlayersStat();
};
