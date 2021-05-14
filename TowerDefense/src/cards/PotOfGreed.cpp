#include "pch.h"
#include "SkillCards.h"
#include "core/Player.h"

TowerDefense::PotOfGreed::PotOfGreed()
	:Card("Pot of Greed", CardType::SKILL, 20, "potOfGreed", "potOfGreedUpgraded")
{
}

void TowerDefense::PotOfGreed::Play()
{
	Player::Get().GetHand()->DrawCard();
	Player::Get().GetHand()->DrawCard();
	if (m_Upgraded)
		Player::Get().GetHand()->DrawCard();
}

std::shared_ptr<TowerDefense::Card> TowerDefense::PotOfGreed::Clone()
{
	auto card = std::make_shared<PotOfGreed>();
	if (m_Upgraded)
		card->Upgrade();
	return card;
}