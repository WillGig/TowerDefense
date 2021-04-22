#include "pch.h"
#include "Giant.h"

TowerDefense::Quirk::Giant::Giant()
	:Quirk("Giant")
{

}

void TowerDefense::Quirk::Giant::Apply(TowerDefense::HeroCard& h)
{
	h.GetTower()->SetDamage(h.GetTower()->GetDamage(Tower::DamageType::PHYSICAL) + 4, Tower::DamageType::PHYSICAL);
	h.GetTower()->SetAttackTime(h.GetTower()->GetAttackTime() * 1.2f);
	h.GetTower()->SetWidth(h.GetTower()->GetWidth() * 2);
	h.GetTower()->SetHeight(h.GetTower()->GetHeight() * 2);
}

std::shared_ptr<TowerDefense::Quirk::Quirk> TowerDefense::Quirk::Giant::Clone()
{
	return std::make_shared<Giant>();
}