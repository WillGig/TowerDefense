#include "pch.h"
#include "BattleReady.h"

TowerDefense::Quirk::BattleReady::BattleReady()
	:Quirk("Battle Ready")
{

}

void TowerDefense::Quirk::BattleReady::Apply(TowerDefense::HeroCard& h)
{
	h.SetCost((int)(h.GetCost() * 0.9f));
}

std::string TowerDefense::Quirk::BattleReady::GetText() const
{
	return "battle-ready";
}

std::shared_ptr<TowerDefense::Quirk::Quirk> TowerDefense::Quirk::BattleReady::Clone()
{
	return std::make_shared<BattleReady>();
}