#include "pch.h"
#include "Artifact.h"
#include "scenes/Combat.h"

TowerDefense::BlessedHandGrenade::BlessedHandGrenade()
	:Artifact("Blessed Hand Grenade"), m_Ready(true), 
	m_Detonate(std::make_unique<Button>(750.0f, 510.0f, 64, 64, "BlessedHandGrenadeButton"))
{}

void TowerDefense::BlessedHandGrenade::CombatRender()
{
	if(m_Ready)
		m_Detonate->Render();
}

void TowerDefense::BlessedHandGrenade::CombatUpdate()
{
	if (!m_Ready)
		return;

	m_Detonate->Update();
	if (m_Detonate->IsClicked())
	{
		auto entities = Combat::GetEntities();
		for (unsigned int i = 0; i < entities->size(); i++)
		{
			auto e = entities->at(i);
			if (e->GetEntityType() == Type::ENEMY)
			{
				auto enemy = std::dynamic_pointer_cast<Enemy::Enemy>(e);
				enemy->TakeDamage(10, GetID(), Tower::DamageType::MAGIC);
				Combat::AddEntity(std::make_shared<AnimationEffect>(e->GetX(), e->GetY(), 100, 100, "fireExplosion", 7, 30));
			}
		}
		m_Ready = false;
	}
}

void TowerDefense::BlessedHandGrenade::OnFightStart()
{
	m_Ready = true;
}