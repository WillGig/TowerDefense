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
	int enemyNum =(int) (Random::GetFloat() * 5);

	if (enemyNum == 0)
	{
		auto e1 = std::make_shared<Beetle>();
		auto e2 = std::make_shared<Beetle>();
		auto e3 = std::make_shared<Beetle>();
		auto e4 = std::make_shared<Beetle>();
		auto e5 = std::make_shared<Beetle>();
		e1->SetDistanceTravelled(GetDistanceTraveled() + 15);
		e2->SetDistanceTravelled(GetDistanceTraveled() + 30);
		e3->SetDistanceTravelled(GetDistanceTraveled() + 45);
		e4->SetDistanceTravelled(GetDistanceTraveled() + 60);
		e5->SetDistanceTravelled(GetDistanceTraveled() + 75);
		Combat::AddEntity(e1);
		Combat::AddEntity(e2);
		Combat::AddEntity(e3);
		Combat::AddEntity(e4);
		Combat::AddEntity(e5);
	}
	else if (enemyNum == 1)
	{
		auto e1 = std::make_shared<Spider>();
		auto e2 = std::make_shared<Spider>();
		auto e3 = std::make_shared<Spider>();
		e1->SetDistanceTravelled(GetDistanceTraveled() + 15);
		e2->SetDistanceTravelled(GetDistanceTraveled() + 30);
		e3->SetDistanceTravelled(GetDistanceTraveled() + 45);
		Combat::AddEntity(e1);
		Combat::AddEntity(e2);
		Combat::AddEntity(e3);
	}
	else if (enemyNum == 2)
	{
		auto e1 = std::make_shared<BlinkBug>();
		auto e2 = std::make_shared<BlinkBug>();
		e1->SetDistanceTravelled(GetDistanceTraveled() + 15);
		e2->SetDistanceTravelled(GetDistanceTraveled() + 30);
		Combat::AddEntity(e1);
		Combat::AddEntity(e2);
	}
	else if (enemyNum == 3)
	{
		auto e = std::make_shared<ToughBeetle>();
		e->SetDistanceTravelled(GetDistanceTraveled() + 15);
		Combat::AddEntity(e);
	}
	else
	{
		auto e = std::make_shared<RunnerBeetle>();
		e->SetDistanceTravelled(GetDistanceTraveled() + 15);
		Combat::AddEntity(e);
	}
}