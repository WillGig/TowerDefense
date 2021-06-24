#include "pch.h"
#include "Curses.h"
#include "core/Player.h"

TowerDefense::Frog::Frog()
	:Card("Frog", CardType::CURSE, 0, "Frog", "FrogUpgraded")
{}

void TowerDefense::Frog::Play()
{}

std::shared_ptr<TowerDefense::Card> TowerDefense::Frog::Clone()
{
	auto card = std::make_shared<Frog>();
	if (m_Upgraded)
		card->Upgrade();
	return card;
}