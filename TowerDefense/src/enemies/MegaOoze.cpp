#include "pch.h"
#include "Enemies.h"
#include "scenes/Combat.h"

void TowerDefense::Enemy::MegaOoze::Destroy()
{
	Enemy::Destroy();

	if (m_Health > 0)
		return;

	std::shared_ptr<DoubleOoze> frontOoze = std::make_shared<DoubleOoze>();
	std::shared_ptr<DoubleOoze> backOoze = std::make_shared<DoubleOoze>();

	frontOoze->SetDistanceTravelled(m_DistanceTraveled + 20);
	backOoze->SetDistanceTravelled(m_DistanceTraveled - 20);

	Combat::AddEntity(frontOoze);
	Combat::AddEntity(backOoze);
}