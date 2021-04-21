#include "pch.h"
#include "NearSighted.h"

TowerDefense::Quirk::NearSighted::NearSighted()
	:Quirk("Nearsighted")
{

}

void TowerDefense::Quirk::NearSighted::Apply(TowerDefense::HeroCard& h)
{
	h.GetTower()->SetRange((int)(h.GetTower()->GetRange() * .7f));
}

std::shared_ptr<TowerDefense::Quirk::Quirk> TowerDefense::Quirk::NearSighted::Clone()
{
	return std::make_shared<NearSighted>();
}