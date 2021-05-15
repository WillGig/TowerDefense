#include "pch.h"
#include "AuraCards.h"
#include "scenes/Combat.h"

TowerDefense::StrongPoisons::StrongPoisons()
	:Card("Strong Poisons", CardType::AURA, 40, "strongPoisons", "strongPoisonsUpgraded")
{
	m_Exhausts = true;
	AddInfoCard(std::make_shared<InfoTile>("auraInfo"));
	AddInfoCard(std::make_shared<InfoTile>("poisonInfo"));
}

void TowerDefense::StrongPoisons::Play()
{
	if(m_Upgraded)
		Combat::AddAura(std::make_shared<EnhancePoison>(0.5f, "1"));
	else
		Combat::AddAura(std::make_shared<EnhancePoison>(1.0f, "2"));
}

std::shared_ptr<TowerDefense::Card> TowerDefense::StrongPoisons::Clone()
{
	auto card = std::make_shared<StrongPoisons>();
	if (m_Upgraded)
		card->Upgrade();
	return card;
}