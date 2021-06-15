#include "pch.h"
#include "quirk.h"

TowerDefense::Quirk::Berserker::Berserker()
	:Quirk("Berserker")
{}

void TowerDefense::Quirk::Berserker::Apply(TowerDefense::HeroCard& h)
{
	h.GetTower()->SetDamage(h.GetTower()->GetDamage(Tower::DamageType::PHYSICAL) + 2, Tower::DamageType::PHYSICAL);
	h.GetTower()->SetDamage(h.GetTower()->GetDamage(Tower::DamageType::MAGIC) - 1, Tower::DamageType::MAGIC);
}

std::shared_ptr<TowerDefense::Quirk::Quirk> TowerDefense::Quirk::Berserker::Clone()
{
	return std::make_shared<Berserker>();
}