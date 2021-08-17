#include "pch.h"
#include "enemies/Enemies.h"
#include "scenes/Combat.h"

void TowerDefense::Enemy::WrithingMass::Update()
{
	Enemy::Update();
	if (m_Health <= 0)
		return;

	for (int i = 0; i < Combat::GetRoundSpeed(); i++)
	{
		if (m_Cast == m_CastTime)
		{
			SummonSpawn();
			m_Cast = 0;
		}
		else
			m_Cast++;
	}
}

void TowerDefense::Enemy::WrithingMass::SummonSpawn()
{
	std::shared_ptr<Enemy> e;

	int enemyNum = Random::GetFloat() * 5;

	if (enemyNum == 0)
	{
		e = std::make_shared<Slime>();
	}
	else if (enemyNum == 1)
	{
		e = std::make_shared<Ooze>();
	}
	else if (enemyNum == 2)
	{
		e = std::make_shared<DoubleSlime>();
	}
	else if (enemyNum == 3)
	{
		e = std::make_shared<JumpingOoze>();
	}
	else if (enemyNum == 4)
	{
		e = std::make_shared<MegaOoze>();
	}

	e->SetDistanceTravelled(GetDistanceTraveled() + 15);
	Combat::AddEntity(e);
}