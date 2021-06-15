#include "pch.h"
#include "quirk.h"

TowerDefense::Quirk::Fighter::Fighter()
	:Quirk("Fighter")
{}

void TowerDefense::Quirk::Fighter::Apply(TowerDefense::HeroCard& h)
{
	h.GetTower()->SetDamage(h.GetTower()->GetDamage(Tower::DamageType::PHYSICAL) + 1, Tower::DamageType::PHYSICAL);
}

std::shared_ptr<TowerDefense::Quirk::Quirk> TowerDefense::Quirk::Fighter::Clone()
{
	return std::make_shared<Fighter>();
}