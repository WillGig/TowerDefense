#include "pch.h"
#include "Alchemist.h"
#include "scenes/Combat.h"
#include "projectiles/Projectiles.h"

TowerDefense::Tower::Alchemist::Alchemist()
	:Tower(0.0f, 0.0f, 32, 32, 120.0f, 100, TowerType::DAMAGE, "res/textures/alchemist.png", "res/textures/alchemistHighlighted.png")
{
	m_MagicDamage = 1.0f;
}

TowerDefense::Tower::Alchemist::Alchemist(float fireTime, int range, float damage)
	: Tower(0.0f, 0.0f, 32, 32, fireTime, range, TowerType::DAMAGE, "res/textures/alchemist.png", "res/textures/alchemistHighlighted.png")
{
	m_Spread = .1f;
	m_MagicDamage = damage;
}

void TowerDefense::Tower::Alchemist::Fire(std::shared_ptr<TowerDefense::Entity> target)
{
	Combat::AddEntity(std::make_shared<TowerDefense::PoisonBomb>(m_X, m_Y, m_Rotation, m_MagicDamage + m_MagicDamageModifier));
}

std::shared_ptr<TowerDefense::Tower::Tower> TowerDefense::Tower::Alchemist::Clone()
{
	auto tower = std::make_shared<Alchemist>(GetAttackTime(), GetRange(), m_MagicDamage);
	tower->SetDamageModifier(m_PhysicalDamageModifier, DamageType::PHYSICAL);
	tower->SetDamageModifier(m_MagicDamageModifier, DamageType::MAGIC);
	return tower;
}