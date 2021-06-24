#include "pch.h"
#include "quirk.h"

TowerDefense::Quirk::Sage::Sage()
	:Quirk("Sage")
{}

void TowerDefense::Quirk::Sage::Apply(TowerDefense::HeroCard& h)
{
	h.GetTower()->SetDamage(h.GetTower()->GetDamage(Tower::DamageType::MAGIC) + 2, Tower::DamageType::MAGIC);
	h.GetTower()->SetDamage(h.GetTower()->GetDamage(Tower::DamageType::PHYSICAL) - 1, Tower::DamageType::PHYSICAL);
}

std::shared_ptr<TowerDefense::Quirk::Quirk> TowerDefense::Quirk::Sage::Clone()
{
	return std::make_shared<Sage>();
}