#include "pch.h"
#include "AuraCards.h"
#include "scenes/Combat.h"

TowerDefense::StunningStrikes::StunningStrikes()
	:Card("Stunning Strikes", CardType::AURA, 50, "stunningStrikes", "stunningStrikesUpgraded")
{
	m_Exhausts = true;
	AddInfoCard(std::make_shared<InfoTile>("auraInfo"));
	AddInfoCard(std::make_shared<InfoTile>("stunInfo"));
}

void TowerDefense::StunningStrikes::Play()
{
	if (m_Upgraded)
		Combat::AddAura(std::make_shared<Aura::StunAttacks>(12));
	else
		Combat::AddAura(std::make_shared<Aura::StunAttacks>(6));
}

std::shared_ptr<TowerDefense::Card> TowerDefense::StunningStrikes::Clone()
{
	auto card = std::make_shared<StunningStrikes>();
	if (m_Upgraded)
		card->Upgrade();
	return card;
}