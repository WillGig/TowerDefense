#include "pch.h"
#include "Gnome.h"

TowerDefense::Quirk::Gnome::Gnome()
	:Quirk("Gnome")
{

}

void TowerDefense::Quirk::Gnome::Apply(TowerDefense::HeroCard& h)
{
	h.GetTower()->SetDamageModifier(h.GetTower()->GetDamageModifier(Tower::DamageType::MAGIC) + 2, Tower::DamageType::MAGIC);
}

std::shared_ptr<TowerDefense::Quirk::Quirk> TowerDefense::Quirk::Gnome::Clone()
{
	return std::make_shared<Gnome>();
}