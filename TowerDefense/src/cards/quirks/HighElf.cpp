#include "pch.h"
#include "quirk.h"

TowerDefense::Quirk::HighElf::HighElf()
	:Quirk("High Elf")
{

}

void TowerDefense::Quirk::HighElf::Apply(TowerDefense::HeroCard& h)
{
	h.GetTower()->SetDamage(h.GetTower()->GetDamage(Tower::DamageType::MAGIC) + 1, Tower::DamageType::MAGIC);
	h.GetTower()->SetAttackTime(h.GetTower()->GetAttackTime() * .9f);
}

std::shared_ptr<TowerDefense::Quirk::Quirk> TowerDefense::Quirk::HighElf::Clone()
{
	return std::make_shared<HighElf>();
}