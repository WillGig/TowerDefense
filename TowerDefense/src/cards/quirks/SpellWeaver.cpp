#include "pch.h"
#include "quirk.h"

TowerDefense::Quirk::Spellweaver::Spellweaver()
	:Quirk("Spellweaver")
{}

void TowerDefense::Quirk::Spellweaver::Apply(TowerDefense::HeroCard& h)
{
	h.GetTower()->SetDamage(h.GetTower()->GetDamage(Tower::DamageType::MAGIC) + 1, Tower::DamageType::MAGIC);
}

std::shared_ptr<TowerDefense::Quirk::Quirk> TowerDefense::Quirk::Spellweaver::Clone()
{
	return std::make_shared<Spellweaver>();
}