#include "pch.h"
#include "quirk.h"

TowerDefense::Quirk::Human::Human()
	:Quirk("Human")
{

}

void TowerDefense::Quirk::Human::Apply(TowerDefense::HeroCard& h)
{
	h.SetCost((int)(h.GetCost() * 0.8f));
}

std::shared_ptr<TowerDefense::Quirk::Quirk> TowerDefense::Quirk::Human::Clone()
{
	return std::make_shared<Human>();
}