#include "pch.h"
#include "AuraCards.h"
#include "scenes/Combat.h"

TowerDefense::EchoLocation::EchoLocation()
	:Card("Echo Location", CardType::AURA, 30, "echoLocation", "echoLocationUpgraded")
{
	m_Exhausts = true;
	AddInfoCard(std::make_shared<InfoTile>("auraInfo"));
}

void TowerDefense::EchoLocation::Play()
{
	Combat::AddAura(std::make_shared<Aura::Sight>());
}

void TowerDefense::EchoLocation::Upgrade()
{
	m_Cost = 10;
}

std::shared_ptr<TowerDefense::Card> TowerDefense::EchoLocation::Clone()
{
	auto card = std::make_shared<EchoLocation>();
	if (m_Upgraded)
		card->Upgrade();
	return card;
}