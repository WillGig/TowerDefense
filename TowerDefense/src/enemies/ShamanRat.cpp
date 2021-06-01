#include "pch.h"
#include "Enemies.h"
#include "scenes/Combat.h"

void TowerDefense::Enemy::ShamanRat::Update()
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

void TowerDefense::Enemy::ShamanRat::Cast()
{
	auto entities = Combat::GetEntities();
	for (unsigned int i = 0; i < entities->size(); i++)
	{
		auto e = entities->at(i);
		if (e->GetEntityType() == Type::ENEMY)
		{
			if (GetDistance(e->GetX(), e->GetY()) < 100)
			{
				auto enemy = std::dynamic_pointer_cast<Enemy>(e);
				enemy->SetMagicResistance(enemy->GetMagicResistance() + 10);
				enemy->SetArmor(enemy->GetArmor() + 10);
			}
		}
	}

	Combat::AddEntity(std::make_shared<AnimationEffect>(m_X, m_Y, 200, 200, "shamanAura", 7, 14));
}