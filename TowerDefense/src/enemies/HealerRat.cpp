#include "pch.h"
#include "Enemies.h"
#include "scenes/Combat.h"

void TowerDefense::Enemy::HealerRat::Update()
{
	Enemy::Update();

	for (int i = 0; i < Combat::GetRoundSpeed(); i++)
	{
		if (m_Cast == m_CastTime)
		{
			Cast();
			m_Cast = 0;
		}
		else
			m_Cast++;
	}
}

void TowerDefense::Enemy::HealerRat::Cast()
{
	auto entities = Combat::GetEntities();
	for (unsigned int i = 0; i < entities->size(); i++)
	{
		auto e = entities->at(i);
		if (e->GetEntityType() == Type::ENEMY)
		{
			if (GetDistance(e->GetX(), e->GetY()) < 100)
				std::dynamic_pointer_cast<Enemy>(e)->ChangeHealth(5);
		}
	}

	Combat::AddEntity(std::make_shared<AnimationEffect>(m_X, m_Y, 200, 200, "healingAura", 7, 14));
}