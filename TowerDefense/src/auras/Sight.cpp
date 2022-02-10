#include "pch.h"
#include "Aura.h"
#include "cards/TowerCard.h"

TowerDefense::Aura::Sight::Sight()
	:Aura("Sight", "sight", "All towers can see\ninvisible enemies.")
{}

void TowerDefense::Aura::Sight::OnCardPlay(std::shared_ptr<Card> c)
{
	if (c->GetCardType() == CardType::TOWER)
		std::dynamic_pointer_cast<TowerCard>(c)->GetHeldTower()->SetSeeInvisilitity(true);
}

void TowerDefense::Aura::Sight::Combine(std::shared_ptr<Aura> other)
{}

const std::string TowerDefense::Aura::Sight::GetSaveData() const
{
	return "Sight";
}