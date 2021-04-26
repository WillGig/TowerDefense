#include "pch.h"
#include "quirk.h"

TowerDefense::Quirk::BattleReady::BattleReady()
	:Quirk("Battle Ready")
{

}

void TowerDefense::Quirk::BattleReady::Apply(TowerDefense::HeroCard& h)
{
	h.SetCost((int)(h.GetCost() * 0.9f));
}

std::shared_ptr<TowerDefense::Quirk::Quirk> TowerDefense::Quirk::BattleReady::Clone()
{
	return std::make_shared<BattleReady>();
}