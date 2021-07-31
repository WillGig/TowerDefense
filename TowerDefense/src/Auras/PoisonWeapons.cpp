#include "pch.h"
#include "Aura.h"
#include "towers/Tower.h"

TowerDefense::PoisonWeapons::PoisonWeapons(float poisonDamage, int poisonDuration, const std::string dmg)
	:Aura("poisonWeapons", "Towers with Physical\nDamage Apply " + dmg + " Poison"),
	m_PoisonDamage(poisonDamage), m_PoisonDuration(poisonDuration)
{
}

void TowerDefense::PoisonWeapons::OnEnemyHit(std::shared_ptr<Enemy::Enemy> e, std::shared_ptr<Entity> source, Tower::DamageType type)
{
	if (source->GetEntityType() == Type::TOWER && type == Tower::DamageType::PHYSICAL)
	{
		auto enemy = std::dynamic_pointer_cast<Enemy::Enemy>(e);
		enemy->ApplyState(std::make_shared<Enemy::Poison>(m_PoisonDuration, m_PoisonDamage, GetID(), enemy));
	}
}