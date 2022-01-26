#include "pch.h"
#include "Enemies.h"
#include "scenes/Combat.h"

void TowerDefense::Enemy::MegaOoze::Destroy()
{
	Enemy::Destroy();

	if (m_Health > 0)
		return;

	auto frontOoze = std::make_shared<DoubleOoze>();
	auto backOoze = std::make_shared<DoubleOoze>();

	frontOoze->SetDistanceTravelled(m_DistanceTraveled + 20);
	backOoze->SetDistanceTravelled(m_DistanceTraveled - 20);

	Combat::AddEntity(frontOoze);
	Combat::AddEntity(backOoze);
}