#include "pch.h"
#include "Enemies.h"
#include "scenes/Combat.h"

void TowerDefense::Enemy::MegaOoze::Destroy()
{
	Enemy::Destroy();

	if (m_Health > 0)
		return;

	std::shared_ptr<DoubleSlime> frontOoze = std::make_shared<DoubleSlime>();
	std::shared_ptr<DoubleSlime> backOoze = std::make_shared<DoubleSlime>();

	frontOoze->SetDistanceTravelled(m_DistanceTraveled + 20);
	backOoze->SetDistanceTravelled(m_DistanceTraveled - 20);

	Combat::AddEntity(frontOoze);
	Combat::AddEntity(backOoze);
}