#include "pch.h"
#include "Enemies.h"
#include "scenes/Combat.h"

void TowerDefense::Enemy::Ooze::Destroy()
{
	Enemy::Destroy();

	if (m_Health > 0)
		return;

	auto slime = std::make_shared<Slime>();
	slime->SetDistanceTravelled(m_DistanceTraveled);
	Combat::AddEntity(slime);
}