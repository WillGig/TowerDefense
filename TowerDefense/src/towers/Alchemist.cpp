#include "pch.h"
#include "Alchemist.h"
#include "scenes/Combat.h"
#include "projectiles/Projectiles.h"
#include "scenes/Base.h"
#include "upgrades/Upgrade.h"

TowerDefense::Tower::Alchemist::Alchemist()
	:Tower(0.0f, 0.0f, 32, 32, 240.0f, 100, TowerType::DAMAGE, "Alchemist"), m_ExplosionRadius(50), 
	m_GoldConversion(0), m_GrenadeSpeed(4.0f), m_SlowPercent(0.0f), m_ResistanceShredPercent(0.0f)
{
	m_MagicDamage = 1.0f;
	m_DamageType = DamageType::MAGIC;
}

TowerDefense::Tower::Alchemist::Alchemist(float fireTime, int range, float damage)
	: Tower(0.0f, 0.0f, 32, 32, fireTime, range, TowerType::DAMAGE, "Alchemist"), m_ExplosionRadius(50), 
	m_GoldConversion(0), m_GrenadeSpeed(4.0f), m_SlowPercent(0.0f), m_ResistanceShredPercent(0.0f)
{
	m_MagicDamage = damage;
	m_DamageType = DamageType::MAGIC;
}

void TowerDefense::Tower::Alchemist::Fire(std::shared_ptr<TowerDefense::Entity> target)
{
	float damage = m_MagicDamage/2.0f;
	if (Random::GetFloat() < m_CritChance)
	{
		damage *= m_CritMultiplier;
		Combat::AddEntity(std::make_shared<AnimationEffect>(m_X, m_Y, 32, 32, "critAnimation", 7, 30));
	}
	auto bomb = std::make_shared<TowerDefense::PoisonBomb>(m_X, m_Y, m_Rotation, damage, m_SlowPercent, m_ResistanceShredPercent, m_GoldConversion, m_ExplosionRadius, GetID());
	bomb->SetSpeed(m_GrenadeSpeed);
	Combat::AddEntity(bomb);
}

bool TowerDefense::Tower::Alchemist::CanUpgrade()
{
	return (GetLevel() < 4 || (GetLevel() < 9 && Base::ContainsScene("AlchemyLab")));
}

std::shared_ptr<std::vector<std::shared_ptr<TowerDefense::Tower::Upgrade>>> TowerDefense::Tower::Alchemist::GetPossibleUpgrades()
{
	auto upgrades = std::make_shared<std::vector<std::shared_ptr<Upgrade>>>();

	if (GetLevel() < 4)
	{
		upgrades->push_back(std::make_shared<AttackSpeed>());
		upgrades->push_back(std::make_shared<Damage>());
		upgrades->push_back(std::make_shared<Range>());
		upgrades->push_back(std::make_shared<Crit>());
	}
	else if (GetLevel() == 4)
	{
		upgrades->push_back(std::make_shared<GrenadeGunner>());
		upgrades->push_back(std::make_shared<TrueAlchemy>());
		upgrades->push_back(std::make_shared<Poisoner>());
	}
	else
	{
		upgrades->push_back(std::make_shared<Damage>());
		upgrades->push_back(std::make_shared<AttackSpeed>());
		upgrades->push_back(std::make_shared<Range>());
		upgrades->push_back(std::make_shared<Crit>());
	}

	return upgrades;
}


std::shared_ptr<TowerDefense::Tower::Tower> TowerDefense::Tower::Alchemist::Clone()
{
	auto tower = std::make_shared<Alchemist>(GetAttackTime(), GetRange(), m_MagicDamage);
	tower->SetDamage(m_PhysicalDamage, DamageType::PHYSICAL);
	tower->SetDamage(m_MagicDamage, DamageType::MAGIC);
	tower->SetCritChance(m_CritChance);
	tower->SetCritMultiplier(m_CritMultiplier);
	tower->SetWidth(m_Width);
	tower->SetHeight(m_Height);
	return tower;
}