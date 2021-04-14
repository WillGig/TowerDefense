#include "pch.h"
#include "Cleric.h"
#include "scenes/Combat.h"
#include "projectiles/Projectiles.h"
#include "buffs/DamageBuff.h"

TowerDefense::Tower::Cleric::Cleric()
	:Tower(0.0f, 0.0f, 32, 32, 60.0f, 75, TowerType::SUPPORT, "res/textures/cleric.png", "res/textures/clericHighlighted.png")
{
	m_DamageBuff = 1.0f;
}

TowerDefense::Tower::Cleric::Cleric(float fireTime, int range, float buff)
	: Tower(0.0f, 0.0f, 32, 32, fireTime, range, TowerType::SUPPORT, "res/textures/cleric.png", "res/textures/clericHighlighted.png")
{
	m_DamageBuff = buff;
}

void TowerDefense::Tower::Cleric::Fire(std::shared_ptr<TowerDefense::Entity> target)
{
	std::shared_ptr<Tower> tower = std::dynamic_pointer_cast<Tower>(target);
	tower->ApplyBuff(std::make_shared<DamageBuff>(150, m_ID, DamageType::MAGIC, m_DamageBuff));
	tower->ApplyBuff(std::make_shared<DamageBuff>(150, m_ID, DamageType::PHYSICAL, m_DamageBuff));
}

std::shared_ptr<TowerDefense::Tower::Tower> TowerDefense::Tower::Cleric::Clone()
{
	auto tower = std::make_shared<Cleric>(GetAttackTime(), GetRange(), m_DamageBuff);
	tower->SetDamageModifier(m_PhysicalDamageModifier, DamageType::PHYSICAL);
	tower->SetDamageModifier(m_MagicDamageModifier, DamageType::MAGIC);
	return tower;
}