#include "pch.h"
#include "Giant.h"
#include "scenes/Combat.h"
#include "projectiles/Projectiles.h"

TowerDefense::Tower::Giant::Giant()
	:Tower(0.0f, 0.0f, 64, 64, 300.0f, 100, TowerType::DAMAGE, "res/textures/giant.png", "res/textures/giantHighlighted.png")
{
	m_Spread = .1f;
	m_PhysicalDamage = 20.0f;
}

TowerDefense::Tower::Giant::Giant(float fireTime, int range, float damage)
	: Tower(0.0f, 0.0f, 64, 64, fireTime, range, TowerType::DAMAGE, "res/textures/giant.png", "res/textures/giantHighlighted.png")
{
	m_Spread = .1f;
	m_PhysicalDamage = damage;
}

void TowerDefense::Tower::Giant::Fire(std::shared_ptr<TowerDefense::Entity> target)
{
	Combat::AddEntity(std::make_shared<TowerDefense::GiantRock>(m_X, m_Y, m_Rotation, m_PhysicalDamage + m_PhysicalDamageModifier));
}

std::shared_ptr<TowerDefense::Tower::Tower> TowerDefense::Tower::Giant::Clone()
{
	auto tower = std::make_shared<Giant>(GetAttackTime(), GetRange(), m_PhysicalDamage);
	tower->SetDamageModifier(m_PhysicalDamageModifier, DamageType::PHYSICAL);
	tower->SetDamageModifier(m_MagicDamageModifier, DamageType::MAGIC);
	tower->SetWidth(m_Width);
	tower->SetHeight(m_Height);
	return tower;
}