#include "pch.h"
#include "Orc.h"

TowerDefense::Quirk::Orc::Orc()
	:Quirk("Orc")
{

}

void TowerDefense::Quirk::Orc::Apply(TowerDefense::HeroCard& h)
{
	h.GetTower()->SetDamageModifier(h.GetTower()->GetDamageModifier(Tower::DamageType::PHYSICAL) + 3, Tower::DamageType::PHYSICAL);
	h.GetTower()->SetDamageModifier(h.GetTower()->GetDamageModifier(Tower::DamageType::MAGIC) - 1, Tower::DamageType::MAGIC);
}

std::shared_ptr<TowerDefense::Quirk::Quirk> TowerDefense::Quirk::Orc::Clone()
{
	return std::make_shared<Orc>();
}