#include "pch.h"
#include "quirk.h"

TowerDefense::Quirk::Farsighted::Farsighted()
	:Quirk("Farsighted")
{

}

void TowerDefense::Quirk::Farsighted::Apply(TowerDefense::HeroCard& h)
{
	h.GetTower()->SetRange((int)(h.GetTower()->GetRange() * 1.3f));
}

std::shared_ptr<TowerDefense::Quirk::Quirk> TowerDefense::Quirk::Farsighted::Clone()
{
	return std::make_shared<Farsighted>();
}