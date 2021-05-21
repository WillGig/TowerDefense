#include "pch.h"
#include "enemies/Enemies.h"
#include "scenes/Combat.h"

void TowerDefense::Enemy::Doubler::Update()
{
	Enemy::Update();
	if (m_Health <= 0)
		return;

	for (int i = 0; i < Combat::GetRoundSpeed(); i++)
	{
		if (m_Time == m_GrowTime)
		{
			ChangeHealth(1);
			m_Time = 0;
		}
		else
			m_Time++;
	}

	if (m_Health == 40)
		Split();
}

void TowerDefense::Enemy::Doubler::Split()
{
	ChangeHealth(-20);
	auto newOoze = std::make_shared<Doubler>();
	newOoze->SetDistanceTravelled(m_DistanceTraveled - 30);
	Combat::AddEntity(newOoze);
}