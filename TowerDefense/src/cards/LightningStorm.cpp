#include "pch.h"
#include "AuraCards.h"
#include "scenes/Combat.h"

TowerDefense::LightningStorm::LightningStorm()
	:Card("Lightning Storm", CardType::AURA, 100, "lightningStorm", "lightningStormUpgraded")
{
	m_Exhausts = true;
	AddInfoCard(std::make_shared<InfoTile>("auraInfo"));
}

void TowerDefense::LightningStorm::Play()
{
	if(m_Upgraded)
		Combat::AddAura(std::make_shared<Aura::Storm>(5));
	else
		Combat::AddAura(std::make_shared<Aura::Storm>(3));
}

std::shared_ptr<TowerDefense::Card> TowerDefense::LightningStorm::Clone()
{
	auto card = std::make_shared<LightningStorm>();
	if (m_Upgraded)
		card->Upgrade();
	return card;
}