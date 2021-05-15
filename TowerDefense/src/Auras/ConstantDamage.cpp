#include "pch.h"
#include "Aura.h"
#include "scenes/Combat.h"

TowerDefense::ConstantDamage::ConstantDamage(float damage, int time, const std::string damagePerTime)
	:Aura("constantDamage", "Deal " + damagePerTime + " to All Enemies"), 
	m_Damage(damage), m_Time(time), m_NextDamage(0)
{
}

void TowerDefense::ConstantDamage::Update()
{
	Aura::Update();

	for (int i = 0; i < Combat::GetRoundSpeed(); i++)
	{
		if (m_NextDamage == 0)
		{
			auto entities = Combat::GetEntities();
			for (unsigned int i = 0; i < entities->size(); i++)
			{
				auto e = entities->at(i);
				if (e->GetEntityType() == Type::ENEMY)
				{
					std::dynamic_pointer_cast<Enemy::Enemy>(e)->TakeDamage(m_Damage, GetID());
					m_NextDamage = m_Time;
				}
			}
		}
		else
			m_NextDamage--;
	}
}