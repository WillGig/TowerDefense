#include "pch.h"
#include "Aura.h"
#include "towers/Tower.h"

TowerDefense::EnhancePoison::EnhancePoison(float extraDamage, const std::string damage)
	:Aura("enhancePoison", "All poisons deal " + damage + "\nextra damage per second"), m_ExtraDamage(extraDamage)
{
}

void TowerDefense::EnhancePoison::OnEnemyHit(std::shared_ptr<Enemy::Enemy> e, std::shared_ptr<Entity> source, Tower::DamageType type)
{
	if (type == Tower::DamageType::POISON)
		e->TakeDamage(m_ExtraDamage, GetID(), Tower::DamageType::TRUE);
}
