#include "pch.h"
#include "AuraCards.h"
#include "scenes/Combat.h"

TowerDefense::ExplosiveStrikes::ExplosiveStrikes()
	:Card("Explosive Strikes", CardType::AURA, 70, "explosiveStrikes", "explosiveStrikesUpgraded")
{
	m_Exhausts = true;
	AddInfoCard(std::make_shared<InfoTile>("auraInfo"));
}

void TowerDefense::ExplosiveStrikes::Play()
{
	if(m_Upgraded)
		Combat::AddAura(std::make_shared<Aura::DeathExplosions>(10));
	else
		Combat::AddAura(std::make_shared<Aura::DeathExplosions>(5));
}

std::shared_ptr<TowerDefense::Card> TowerDefense::ExplosiveStrikes::Clone()
{
	auto card = std::make_shared<ExplosiveStrikes>();
	if (m_Upgraded)
		card->Upgrade();
	return card;
}