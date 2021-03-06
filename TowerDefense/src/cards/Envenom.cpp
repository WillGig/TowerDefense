#include "pch.h"
#include "AuraCards.h"
#include "scenes/Combat.h"

TowerDefense::Envenom::Envenom()
	:Card("Envenom", CardType::AURA, 40, "envenom", "envenomUpgraded")
{
	m_Exhausts = true;
	AddInfoCard(std::make_shared<InfoTile>("auraInfo"));
	AddInfoCard(std::make_shared<InfoTile>("poisonInfo"));
}

void TowerDefense::Envenom::Play()
{
	if (m_Upgraded)
		Combat::AddAura(std::make_shared<Aura::PoisonWeapons>(1.0f, 90));
	else
		Combat::AddAura(std::make_shared<Aura::PoisonWeapons>(0.5f, 90));
}

std::shared_ptr<TowerDefense::Card> TowerDefense::Envenom::Clone()
{
	auto card = std::make_shared<Envenom>();
	if (m_Upgraded)
		card->Upgrade();
	return card;
}