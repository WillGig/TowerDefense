#include "pch.h"
#include "AuraCards.h"
#include "scenes/Combat.h"

TowerDefense::LifeAura::LifeAura()
	:Card("Life Aura", CardType::AURA, 50, "lifeAura", "lifeAuraUpgraded")
{
	m_Exhausts = true;
	AddInfoCard(std::make_shared<InfoTile>("exhaustInfo"));
}

void TowerDefense::LifeAura::Play()
{
	if(m_Upgraded)
		Combat::AddAura(std::make_shared<LifeSteal>(2));
	else
		Combat::AddAura(std::make_shared<LifeSteal>(1));
}

std::shared_ptr<TowerDefense::Card> TowerDefense::LifeAura::Clone()
{
	auto card = std::make_shared<LifeAura>();
	if (m_Upgraded)
		card->Upgrade();
	return card;
}