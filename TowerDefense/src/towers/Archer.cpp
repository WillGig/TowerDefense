#include "pch.h"
#include "Archer.h"
#include "scenes/Combat.h"
#include "projectiles/Projectiles.h"

TowerDefense::Tower::Archer::Archer()
	:Tower(0.0f, 0.0f, 32, 32, 20.0f, 100, TowerType::DAMAGE, "Archer")
{
	m_Spread = .1f;
	m_PhysicalDamage = 1.0f;
}

TowerDefense::Tower::Archer::Archer(float fireTime, int range, float damage)
	: Tower(0.0f, 0.0f, 32, 32, fireTime, range, TowerType::DAMAGE, "Archer")
{
	m_Spread = .1f;
	m_PhysicalDamage = damage;
}

void TowerDefense::Tower::Archer::Fire(std::shared_ptr<TowerDefense::Entity> target)
{
	float damage = m_PhysicalDamage + m_PhysicalDamageModifier;
	if (Random::GetFloat() < m_CritChance)
	{
		damage *= m_CritMultiplier;
		Combat::AddEntity(std::make_shared<AnimationEffect>(m_X, m_Y, 32, 32, "critAnimation", 7, 30));
	}
	Combat::AddEntity(std::make_shared<TowerDefense::Arrow>(m_X, m_Y, m_Rotation, damage));
}

std::shared_ptr<TowerDefense::Tower::Tower> TowerDefense::Tower::Archer::Clone()
{
	auto tower = std::make_shared<Archer>(GetAttackTime(), GetRange(), m_PhysicalDamage);
	tower->SetDamageModifier(m_PhysicalDamageModifier, DamageType::PHYSICAL);
	tower->SetDamageModifier(m_MagicDamageModifier, DamageType::MAGIC);
	tower->SetCritChance(m_CritChance);
	tower->SetCritMultiplier(m_CritMultiplier);
	tower->SetWidth(m_Width);
	tower->SetHeight(m_Height);
	return tower;
}