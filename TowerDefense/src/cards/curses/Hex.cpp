#include "pch.h"
#include "Curses.h"
#include "core/Player.h"

TowerDefense::Hex::Hex()
	:Card("Hex", CardType::CURSE, 0, "Hex", "HexUpgraded")
{
	m_Exhausts = true;
}

void TowerDefense::Hex::Play() {}

std::shared_ptr<TowerDefense::Card> TowerDefense::Hex::Clone()
{
	auto card = std::make_shared<Hex>();
	if (m_Upgraded)
		card->Upgrade();
	return card;
}