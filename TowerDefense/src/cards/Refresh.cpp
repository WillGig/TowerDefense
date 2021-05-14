#include "pch.h"
#include "SkillCards.h"
#include "core/Player.h"

TowerDefense::Refresh::Refresh()
	:Card("Refresh", CardType::SKILL, 40, "refresh", "refreshUpgraded")
{
}

bool TowerDefense::Refresh::Play()
{
	auto hand = Player::Get().GetHand();
	hand->DiscardHand();
	for (int i = 0; i < 4; i++)
		hand->DrawCard();
	if (m_Upgraded)
		hand->DrawCard();
	return true;
}

std::shared_ptr<TowerDefense::Card> TowerDefense::Refresh::Clone()
{
	auto card = std::make_shared<Refresh>();
	if (m_Upgraded)
		card->Upgrade();
	return card;
}