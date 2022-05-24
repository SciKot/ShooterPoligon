// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "UI/SPPlayerHUDWidget.h"

#include "Components/SPHealthComponent.h"

float USPPlayerHUDWidget::GetHealthPercent() const
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player) return 0.0f;

	const auto Component = Player->GetComponentByClass(USPHealthComponent::StaticClass());
	const auto HealthComponent = Cast<USPHealthComponent>(Component);
	if (!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();
}
