#include "pch.h"
#include "quirk.h"

TowerDefense::Quirk::Nearsighted::Nearsighted()
	:Quirk("Nearsighted")
{

}

void TowerDefense::Quirk::Nearsighted::Apply(TowerDefense::HeroCard& h)
{
	h.GetTower()->SetRange((int)(h.GetTower()->GetRange() * .7f));
}

std::shared_ptr<TowerDefense::Quirk::Quirk> TowerDefense::Quirk::Nearsighted::Clone()
{
	return std::make_shared<Nearsighted>();
}