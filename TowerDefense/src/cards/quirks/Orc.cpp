#include "pch.h"
#include "Orc.h"

TowerDefense::Quirk::Orc::Orc()
	:Quirk("Orc")
{

}

void TowerDefense::Quirk::Orc::Apply(TowerDefense::HeroCard& h)
{
	h.GetTower()->SetDamage(h.GetTower()->GetDamage(Tower::DamageType::PHYSICAL) + 3, Tower::DamageType::PHYSICAL);
	h.GetTower()->SetDamage(h.GetTower()->GetDamage(Tower::DamageType::MAGIC) - 1, Tower::DamageType::MAGIC);
}

std::shared_ptr<TowerDefense::Quirk::Quirk> TowerDefense::Quirk::Orc::Clone()
{
	return std::make_shared<Orc>();
}