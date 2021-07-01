#include "pch.h"
#include "Archer.h"
#include "scenes/Combat.h"
#include "projectiles/Projectiles.h"
#include "towers/upgrades/Upgrade.h"

TowerDefense::Tower::Archer::Archer()
	:Tower(0.0f, 0.0f, 32, 32, 40.0f, 100, TowerType::DAMAGE, "Archer"),
	m_NumberOfArrows(1)
{
	m_Spread = .1f;
	m_PhysicalDamage = 1.0f;
	m_DamageType = DamageType::PHYSICAL;
}

TowerDefense::Tower::Archer::Archer(float fireTime, int range, float damage)
	: Tower(0.0f, 0.0f, 32, 32, fireTime, range, TowerType::DAMAGE, "Archer"),
	m_NumberOfArrows(1)
{
	m_Spread = .1f;
	m_PhysicalDamage = damage;
	m_DamageType = DamageType::PHYSICAL;
}

void TowerDefense::Tower::Archer::Fire(std::shared_ptr<TowerDefense::Entity> target)
{
	float damage = m_PhysicalDamage;
	if (Random::GetFloat() < m_CritChance)
	{
		damage *= m_CritMultiplier;
		Combat::AddEntity(std::make_shared<AnimationEffect>(m_X, m_Y, 32, 32, "critAnimation", 7, 30));
	}

	for (int i = 0; i < m_NumberOfArrows; i++) {
		float armorReduction = 0.0f;
		if (Random::GetFloat() < m_ArmorPenChance)
			armorReduction = m_ArmorPenReduction;
		float angle = (i - ((m_NumberOfArrows - 1) / 2.0f)) * (90.0f / m_NumberOfArrows);
		Combat::AddEntity(std::make_shared<TowerDefense::Arrow>(m_X, m_Y, m_Rotation + angle, damage, armorReduction, GetID()));
	}
}

std::shared_ptr<TowerDefense::Tower::Upgrade> TowerDefense::Tower::Archer::GetRandomTowerUpgrade(std::shared_ptr<std::vector<std::shared_ptr<Upgrade>>> exclude)
{
	std::shared_ptr<Upgrade> upgrade;

	while (!upgrade || ContainsUpgrade(exclude, upgrade)) {
		int randomUpgrade = (int)(Random::GetFloat() * 6.0f);
		if (randomUpgrade == 0)
			upgrade = std::make_shared<AttackSpeed>();
		else if (randomUpgrade == 1)
			upgrade = std::make_shared<Damage>();
		else if (randomUpgrade == 2)
			upgrade = std::make_shared<Range>();
		else if (randomUpgrade == 3)
			upgrade = std::make_shared<Crit>();
		else if (randomUpgrade == 4)
			upgrade = std::make_shared<Multishot>();
		else if (randomUpgrade == 5)
			upgrade = std::make_shared<ArmorPen>();
	}
	return upgrade;
}

std::shared_ptr<TowerDefense::Tower::Tower> TowerDefense::Tower::Archer::Clone()
{
	auto tower = std::make_shared<Archer>(GetAttackTime(), GetRange(), m_PhysicalDamage);
	tower->SetDamage(m_PhysicalDamage, DamageType::PHYSICAL);
	tower->SetDamage(m_MagicDamage, DamageType::MAGIC);
	tower->SetCritChance(m_CritChance);
	tower->SetCritMultiplier(m_CritMultiplier);
	tower->SetWidth(m_Width);
	tower->SetHeight(m_Height);
	return tower;
}