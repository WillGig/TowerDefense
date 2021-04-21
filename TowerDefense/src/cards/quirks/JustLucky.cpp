#include "pch.h"
#include "JustLucky.h"

TowerDefense::Quirk::JustLucky::JustLucky()
	:Quirk("Just Lucky")
{

}

void TowerDefense::Quirk::JustLucky::Apply(TowerDefense::HeroCard& h)
{
	h.GetTower()->SetCritChance(h.GetTower()->GetCritChance()+0.1f);
}

std::shared_ptr<TowerDefense::Quirk::Quirk> TowerDefense::Quirk::JustLucky::Clone()
{
	return std::make_shared<JustLucky>();
}