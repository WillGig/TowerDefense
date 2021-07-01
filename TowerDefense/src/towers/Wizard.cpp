#include "pch.h"
#include "Wizard.h"
#include "scenes/Combat.h"
#include "projectiles/Projectiles.h"
#include "upgrades/Upgrade.h"

TowerDefense::Tower::Wizard::Wizard()
	:Tower(0.0f, 0.0f, 32, 32, 100.0f, 150, TowerType::DAMAGE, "Wizard"),
	m_NumberOfMissiles(3)
{
	m_MagicDamage = 1.0f;
	m_DamageType = DamageType::MAGIC;
}

TowerDefense::Tower::Wizard::Wizard(float fireTime, int range, float damage, int numberOfMissiles)
	: Tower(0.0f, 0.0f, 32, 32, fireTime, range, TowerType::DAMAGE, "Wizard"),
	m_NumberOfMissiles(numberOfMissiles)
{
	m_MagicDamage = damage;
	m_DamageType = DamageType::MAGIC;
}

void TowerDefense::Tower::Wizard::Fire(std::shared_ptr<TowerDefense::Entity> target)
{
	float damage = m_MagicDamage;
	if (Random::GetFloat() < m_CritChance)
	{
		damage *= m_CritMultiplier;
		Combat::AddEntity(std::make_shared<AnimationEffect>(m_X, m_Y, 32, 32, "critAnimation", 7, 30));
	}
	for (int i = 0; i < m_NumberOfMissiles; i++) {
		float angle = (i - ((m_NumberOfMissiles - 1) / 2.0f)) * (180.0f / m_NumberOfMissiles);
		Combat::AddEntity(std::make_shared<TowerDefense::MagicMissile>(m_X, m_Y, m_Rotation + angle, damage, GetID()));
	}
}

std::shared_ptr<std::vector<std::shared_ptr<TowerDefense::Tower::Upgrade>>> TowerDefense::Tower::Wizard::GetPossibleUpgrades()
{
	auto upgrades = std::make_shared<std::vector<std::shared_ptr<Upgrade>>>();
	upgrades->push_back(std::make_shared<AttackSpeed>());
	upgrades->push_back(std::make_shared<Damage>());
	upgrades->push_back(std::make_shared<Range>());
	upgrades->push_back(std::make_shared<Crit>());
	upgrades->push_back(std::make_shared<MoreMissiles>());

	return upgrades;
}

std::shared_ptr<TowerDefense::Tower::Tower> TowerDefense::Tower::Wizard::Clone()
{
	auto tower = std::make_shared<Wizard>(GetAttackTime(), GetRange(), m_MagicDamage, m_NumberOfMissiles);
	tower->SetDamage(m_PhysicalDamage, DamageType::PHYSICAL);
	tower->SetDamage(m_MagicDamage, DamageType::MAGIC);
	tower->SetCritChance(m_CritChance);
	tower->SetCritMultiplier(m_CritMultiplier);
	tower->SetWidth(m_Width);
	tower->SetHeight(m_Height);
	return tower;
}