#include "pch.h"
#include "Artifact.h"
#include "cards/TowerCard.h"

TowerDefense::BlessingOfTheBat::BlessingOfTheBat()
	:Artifact("Blessing of the Bat")
{}

void TowerDefense::BlessingOfTheBat::OnCardPlay(std::shared_ptr<Card> c)
{
	if (c->GetCardType() == CardType::TOWER)
		std::dynamic_pointer_cast<TowerCard>(c)->GetHeldTower()->SetSeeInvisilitity(true);
}