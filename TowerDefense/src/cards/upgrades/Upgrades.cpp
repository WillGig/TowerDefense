#include "pch.h"
#include "Upgrades.h"

void TowerDefense::AttackSpeedUpgrade::UpgradeHero(HeroCard& hero)
{
	hero.GetTower()->SetAttackTime(hero.GetTower()->GetAttackTime() * (1.0f - m_Percent));
}

void TowerDefense::DamageUpgrade::UpgradeHero(HeroCard& hero)
{
	hero.GetTower()->SetDamageModifier(hero.GetTower()->GetDamageModifier(Tower::DamageType::PHYSICAL) + m_PhysicalIncrease, Tower::DamageType::PHYSICAL);
	hero.GetTower()->SetDamageModifier(hero.GetTower()->GetDamageModifier(Tower::DamageType::MAGIC) + m_MagicIncrease, Tower::DamageType::MAGIC);
}

void TowerDefense::RangeUpgrade::UpgradeHero(HeroCard& hero)
{
	hero.GetTower()->SetRange(hero.GetTower()->GetRange() + m_RangeIncrease);
}