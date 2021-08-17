#include "pch.h"
#include "Enemies.h"
#include "scenes/Combat.h"

void TowerDefense::Enemy::DoubleSlime::Destroy()
{
	Enemy::Destroy();

	if (m_Health > 0)
		return;

	std::shared_ptr<Slime> frontOoze = std::make_shared<Slime>();
	std::shared_ptr<Slime> backOoze = std::make_shared<Slime>();

	frontOoze->SetDistanceTravelled(m_DistanceTraveled + 15);
	backOoze->SetDistanceTravelled(m_DistanceTraveled - 15);

	Combat::AddEntity(frontOoze);
	Combat::AddEntity(backOoze);
}