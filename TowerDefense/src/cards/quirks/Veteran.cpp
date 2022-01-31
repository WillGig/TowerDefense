#include "pch.h"
#include "quirk.h"
#include "towers/upgrades/Upgrade.h"

TowerDefense::Quirk::Veteran::Veteran()
	:Quirk("Veteran")
{}

void TowerDefense::Quirk::Veteran::Apply(TowerDefense::HeroCard& h)
{
	auto tower = h.GetTower();
	auto upgrades = tower->GetTowerUpgrades();
	upgrades->at(0)->UpgradeTower(tower);
	upgrades->clear();
}

std::shared_ptr<TowerDefense::Quirk::Quirk> TowerDefense::Quirk::Veteran::Clone()
{
	return std::make_shared<Veteran>();
}