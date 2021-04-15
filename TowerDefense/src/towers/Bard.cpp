#include "pch.h"
#include "Bard.h"
#include "scenes/Combat.h"
#include "projectiles/Projectiles.h"
#include "buffs/SpeedBuff.h"

TowerDefense::Tower::Bard::Bard()
	:Tower(0.0f, 0.0f, 32, 32, 60.0f, 75, TowerType::SUPPORT, "res/textures/bard.png", "res/textures/bardHighlighted.png")
{
	m_AttackSpeedBuff = 1.25f;
}

TowerDefense::Tower::Bard::Bard(float fireTime, int range, float buff)
	: Tower(0.0f, 0.0f, 32, 32, fireTime, range, TowerType::SUPPORT, "res/textures/bard.png", "res/textures/bardHighlighted.png")
{
	m_AttackSpeedBuff = buff;
}

void TowerDefense::Tower::Bard::Fire(std::shared_ptr<TowerDefense::Entity> target)
{
	std::shared_ptr<Tower> tower = std::dynamic_pointer_cast<Tower>(target);
	tower->ApplyBuff(std::make_shared<SpeedBuff>(150, m_ID, m_AttackSpeedBuff));
}

std::shared_ptr<TowerDefense::Tower::Tower> TowerDefense::Tower::Bard::Clone()
{
	auto tower = std::make_shared<Bard>(GetAttackTime(), GetRange(), m_AttackSpeedBuff);
	tower->SetDamageModifier(m_PhysicalDamageModifier, DamageType::PHYSICAL);
	tower->SetDamageModifier(m_MagicDamageModifier, DamageType::MAGIC);
	tower->SetWidth(m_Width);
	tower->SetHeight(m_Height);
	return tower;
}