#include "pch.h"
#include "Dwarf.h"

TowerDefense::Quirk::Dwarf::Dwarf()
	:Quirk("Dwarf")
{

}

void TowerDefense::Quirk::Dwarf::Apply(TowerDefense::HeroCard& h)
{
	h.GetTower()->SetDamageModifier(h.GetTower()->GetDamageModifier(Tower::DamageType::PHYSICAL) + 2, Tower::DamageType::PHYSICAL);
}

std::shared_ptr<TowerDefense::Quirk::Quirk> TowerDefense::Quirk::Dwarf::Clone()
{
	return std::make_shared<Dwarf>();
}