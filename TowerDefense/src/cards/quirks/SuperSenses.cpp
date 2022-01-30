#include "pch.h"
#include "Quirk.h"

TowerDefense::Quirk::SuperSenses::SuperSenses()
	:Quirk("Super Senses")
{}

void TowerDefense::Quirk::SuperSenses::Apply(TowerDefense::HeroCard& h)
{
	h.GetTower()->SetSeeInvisilitity(true);
}

std::shared_ptr<TowerDefense::Quirk::Quirk> TowerDefense::Quirk::SuperSenses::Clone()
{
	return std::make_shared<SuperSenses>();
}