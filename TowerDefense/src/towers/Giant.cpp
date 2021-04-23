#include "pch.h"
#include "Giant.h"
#include "scenes/Combat.h"
#include "projectiles/Projectiles.h"

TowerDefense::Tower::Giant::Giant()
	:Tower(0.0f, 0.0f, 64, 64, 300.0f, 100, TowerType::DAMAGE, "GIANT")
{
	m_Spread = .1f;
	m_PhysicalDamage = 20.0f;
	m_DamageType = DamageType::PHYSICAL;
}

TowerDefense::Tower::Giant::Giant(float fireTime, int range, float damage)
	: Tower(0.0f, 0.0f, 64, 64, fireTime, range, TowerType::DAMAGE, "GIANT")
{
	m_Spread = .1f;
	m_PhysicalDamage = damage;
	m_DamageType = DamageType::PHYSICAL;
}

void TowerDefense::Tower::Giant::Fire(std::shared_ptr<TowerDefense::Entity> target)
{
	float damage = m_PhysicalDamage;
	if (Random::GetFloat() < m_CritChance)
	{
		damage *= m_CritMultiplier;
		Combat::AddEntity(std::make_shared<AnimationEffect>(m_X, m_Y, 32, 32, "critAnimation", 7, 30));
	}
	Combat::AddEntity(std::make_shared<TowerDefense::GiantRock>(m_X, m_Y, m_Rotation, damage, GetID()));
}

std::shared_ptr<TowerDefense::Tower::Tower> TowerDefense::Tower::Giant::Clone()
{
	auto tower = std::make_shared<Giant>(GetAttackTime(), GetRange(), m_PhysicalDamage);
	tower->SetDamage(m_PhysicalDamage, DamageType::PHYSICAL);
	tower->SetDamage(m_MagicDamage, DamageType::MAGIC);
	tower->SetCritChance(m_CritChance);
	tower->SetCritMultiplier(m_CritMultiplier);
	tower->SetWidth(m_Width);
	tower->SetHeight(m_Height);
	return tower;
}