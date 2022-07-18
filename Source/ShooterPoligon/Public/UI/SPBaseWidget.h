// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"

#include "SPBaseWidget.generated.h"

UCLASS()
class SHOOTERPOLIGON_API USPBaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Show();

protected:
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* ShowAnimation;
};
