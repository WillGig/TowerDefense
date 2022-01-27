#include "pch.h"
#include "Curses.h"
#include "core/Player.h"

TowerDefense::Sludge::Sludge()
	:Card("Sludge", CardType::CURSE, 20, "Sludge", "SludgeUpgraded")
{
	m_Exhausts = true;
}

void TowerDefense::Sludge::Play() {}

void TowerDefense::Sludge::Upgrade()
{
	Card::Upgrade();
	m_Cost = 10;
}

std::shared_ptr<TowerDefense::Card> TowerDefense::Sludge::Clone()
{
	auto card = std::make_shared<Sludge>();
	if (m_Upgraded)
		card->Upgrade();
	return card;
}