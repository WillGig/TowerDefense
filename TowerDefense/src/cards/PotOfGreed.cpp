#include "pch.h"
#include "PotOfGreed.h"
#include "core/Player.h"

TowerDefense::PotOfGreed::PotOfGreed()
	:Card("Pot of Greed", CardType::SKILL, 20, "potOfGreed", "potOfGreedUpgraded")
{
}

bool TowerDefense::PotOfGreed::Play()
{
	Player::Get().GetHand()->DrawCard();
	Player::Get().GetHand()->DrawCard();
	if (m_Upgraded)
		Player::Get().GetHand()->DrawCard();
	return true;
}

std::shared_ptr<TowerDefense::Card> TowerDefense::PotOfGreed::Clone()
{
	auto card = std::make_shared<PotOfGreed>();
	if (m_Upgraded)
		card->Upgrade();
	return card;
}