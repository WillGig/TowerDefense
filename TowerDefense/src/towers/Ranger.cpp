#include "pch.h"
#include "Ranger.h"
#include "scenes/Combat.h"
#include "projectiles/Projectiles.h"
#include "upgrades/Upgrade.h"
#include "scenes/Base.h"

TowerDefense::Tower::Ranger::Ranger()
	:Tower(0.0f, 0.0f, 32, 32, 30.0f, 150, TowerType::DAMAGE, "Ranger")
{
	m_Spread = .1f;
	m_PhysicalDamage = 1.0f;
	m_DamageType = DamageType::PHYSICAL;
}

TowerDefense::Tower::Ranger::Ranger(float fireTime, int range, float damage)
	: Tower(0.0f, 0.0f, 32, 32, fireTime, range, TowerType::DAMAGE, "Ranger")
{
	m_Spread = .1f;
	m_PhysicalDamage = damage;
	m_DamageType = DamageType::PHYSICAL;
}

void TowerDefense::Tower::Ranger::Fire(std::shared_ptr<TowerDefense::Entity> target)
{
	float damage = m_PhysicalDamage;
	if (Random::GetFloat() < m_CritChance)
	{
		damage *= m_CritMultiplier;
		Combat::AddEntity(std::make_shared<AnimationEffect>(m_X, m_Y, 32, 32, "critAnimation", 7, 30));
	}

	float armorReduction = 0.0f;
	if (Random::GetFloat() < m_ArmorPenChance)
		armorReduction = m_ArmorPenReduction;

	Combat::AddEntity(std::make_shared<TowerDefense::Arrow>(m_X, m_Y, m_Rotation, damage, armorReduction, GetID()));
}

std::shared_ptr<std::vector<std::shared_ptr<TowerDefense::Tower::Upgrade>>> TowerDefense::Tower::Ranger::GetPossibleUpgrades()
{
	auto upgrades = std::make_shared<std::vector<std::shared_ptr<Upgrade>>>();
	upgrades->push_back(std::make_shared<AttackSpeed>());
	upgrades->push_back(std::make_shared<Damage>());
	upgrades->push_back(std::make_shared<Range>());
	upgrades->push_back(std::make_shared<Crit>());
	upgrades->push_back(std::make_shared<ArmorPen>());

	return upgrades;
}

bool TowerDefense::Tower::Ranger::CanUpgrade()
{
	return (GetLevel() < 4 || (GetLevel() < 9 && Base::ContainsScene("")));
}

std::shared_ptr<TowerDefense::Tower::Tower> TowerDefense::Tower::Ranger::Clone()
{
	auto tower = std::make_shared<Ranger>(GetAttackTime(), GetRange(), m_PhysicalDamage);
	tower->SetDamage(m_PhysicalDamage, DamageType::PHYSICAL);
	tower->SetDamage(m_MagicDamage, DamageType::MAGIC);
	tower->SetCritChance(m_CritChance);
	tower->SetCritMultiplier(m_CritMultiplier);
	tower->SetWidth(m_Width);
	tower->SetHeight(m_Height);
	return tower;
}