#include "pch.h"
#include "quirk.h"

TowerDefense::Quirk::Veteran::Veteran()
	:Quirk("Veteran")
{

}

void TowerDefense::Quirk::Veteran::Apply(TowerDefense::HeroCard& h)
{
	h.GetUpgrades()->SetSelectedCard((int)(Random::GetFloat() * h.GetUpgrades()->NumberOfChoices()));
	h.Upgrade();
}

std::shared_ptr<TowerDefense::Quirk::Quirk> TowerDefense::Quirk::Veteran::Clone()
{
	return std::make_shared<Veteran>();
}