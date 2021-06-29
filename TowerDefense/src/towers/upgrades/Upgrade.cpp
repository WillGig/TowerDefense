#include "pch.h"
#include "Upgrade.h"

TowerDefense::Tower::Upgrade::Upgrade(const std::string name)
	:Button(0.0f, 0.0f, 50, 50, name), m_Name(name)
{}

TowerDefense::Tower::AttackSpeed::AttackSpeed()
	:Upgrade("attackSpeedUpgrade")
{}

void TowerDefense::Tower::AttackSpeed::UpgradeTower(std::shared_ptr<Tower> t)
{
	t->SetAttackTime(t->GetAttackTime() * 0.75f);
	t->SetLevel(t->GetLevel() + 1);
}

TowerDefense::Tower::Damage::Damage()
	:Upgrade("damageUpgrade")
{}

void TowerDefense::Tower::Damage::UpgradeTower(std::shared_ptr<Tower> t)
{
	t->SetDamage(1.0f + t->GetDamage(t->GetDamageType()), t->GetDamageType());
	t->SetLevel(t->GetLevel() + 1);
}

TowerDefense::Tower::Range::Range()
	:Upgrade("rangeUpgrade")
{}

void TowerDefense::Tower::Range::UpgradeTower(std::shared_ptr<Tower> t)
{
	t->SetRange(t->GetRange() + 25);
	t->SetLevel(t->GetLevel() + 1);
}