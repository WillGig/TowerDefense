#include "pch.h"
#include "WoodElf.h"

TowerDefense::Quirk::WoodElf::WoodElf()
	:Quirk("Wood Elf")
{

}

void TowerDefense::Quirk::WoodElf::Apply(TowerDefense::HeroCard& h)
{
	h.GetTower()->SetDamage(h.GetTower()->GetDamage(Tower::DamageType::PHYSICAL) + 1, Tower::DamageType::PHYSICAL);
	h.GetTower()->SetAttackTime(h.GetTower()->GetAttackTime() * .9f);
}

std::shared_ptr<TowerDefense::Quirk::Quirk> TowerDefense::Quirk::WoodElf::Clone()
{
	return std::make_shared<WoodElf>();
}