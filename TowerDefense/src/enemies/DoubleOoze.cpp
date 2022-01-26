#include "pch.h"
#include "Enemies.h"
#include "scenes/Combat.h"

void TowerDefense::Enemy::DoubleOoze::Destroy()
{
	Enemy::Destroy();

	if (m_Health > 0)
		return;

	std::shared_ptr<Ooze> frontOoze = std::make_shared<Ooze>();
	std::shared_ptr<Ooze> backOoze = std::make_shared<Ooze>();

	frontOoze->SetDistanceTravelled(m_DistanceTraveled + 15);
	backOoze->SetDistanceTravelled(m_DistanceTraveled - 15);

	Combat::AddEntity(frontOoze);
	Combat::AddEntity(backOoze);
}