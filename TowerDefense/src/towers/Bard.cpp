#include "pch.h"
#include "Bard.h"
#include "scenes/Combat.h"
#include "projectiles/Projectiles.h"
#include "buffs/SpeedBuff.h"
#include "scenes/Base.h"
#include "upgrades/Upgrade.h"

TowerDefense::Tower::Bard::Bard()
	:Tower(0.0f, 0.0f, 32, 32, 60.0f, 75, TowerType::SUPPORT, "Bard")
{
	m_MagicDamage = 1.0f;
	m_DamageType = DamageType::MAGIC;
}

TowerDefense::Tower::Bard::Bard(float fireTime, int range, float buff)
	: Tower(0.0f, 0.0f, 32, 32, fireTime, range, TowerType::SUPPORT, "Bard")
{
	m_MagicDamage = buff;
	m_DamageType = DamageType::MAGIC;
}

void TowerDefense::Tower::Bard::Fire(std::shared_ptr<TowerDefense::Entity> target)
{
	std::shared_ptr<Tower> tower = std::dynamic_pointer_cast<Tower>(target);
	tower->ApplyBuff(std::make_shared<SpeedBuff>(150, m_ID, 1.0f + m_MagicDamage*0.25f));
}

std::shared_ptr<std::vector<std::shared_ptr<TowerDefense::Tower::Upgrade>>> TowerDefense::Tower::Bard::GetPossibleUpgrades()
{
	auto upgrades = std::make_shared<std::vector<std::shared_ptr<Upgrade>>>();

	if (GetLevel() < 4)
	{
		upgrades->push_back(std::make_shared<AttackSpeed>());
		upgrades->push_back(std::make_shared<Damage>());
		upgrades->push_back(std::make_shared<Range>());
	}
	else if (GetLevel() == 4)
	{
		upgrades->push_back(std::make_shared<Pacifist>());
		upgrades->push_back(std::make_shared<Empowerer>());
		upgrades->push_back(std::make_shared<DisarmingWords>());
	}
	else
	{
		upgrades->push_back(std::make_shared<AttackSpeed>());
		upgrades->push_back(std::make_shared<Damage>());
		upgrades->push_back(std::make_shared<Range>());
	}

	return upgrades;
}

bool TowerDefense::Tower::Bard::CanUpgrade()
{
	return (GetLevel() < 4 || (GetLevel() < 9 && Base::ContainsScene("MusicHall")));
}

std::shared_ptr<TowerDefense::Tower::Tower> TowerDefense::Tower::Bard::Clone()
{
	auto tower = std::make_shared<Bard>(GetAttackTime(), GetRange(), m_MagicDamage);
	tower->SetDamage(m_PhysicalDamage, DamageType::PHYSICAL);
	tower->SetDamage(m_MagicDamage, DamageType::MAGIC);
	tower->SetCritChance(m_CritChance);
	tower->SetCritMultiplier(m_CritMultiplier);
	tower->SetWidth(m_Width);
	tower->SetHeight(m_Height);
	return tower;
}