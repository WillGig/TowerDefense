#include "pch.h"
#include "Curses.h"
#include "core/Player.h"

TowerDefense::Infection::Infection()
	:Card("Infection", CardType::CURSE, 50, "Infection", "InfectionUpgraded")
{
	m_Exhausts = true;
}

void TowerDefense::Infection::Play() {}

void TowerDefense::Infection::OnUnplayed()
{
	Player::Get().AddToDiscardPile(std::make_shared<Infection>());
}

void TowerDefense::Infection::Upgrade()
{
	Card::Upgrade();
	m_Cost = 30;
}

std::shared_ptr<TowerDefense::Card> TowerDefense::Infection::Clone()
{
	auto card = std::make_shared<Infection>();
	if (m_Upgraded)
		card->Upgrade();
	return card;
}