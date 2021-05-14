#include "pch.h"
#include "SkillCards.h"
#include "core/Player.h"

TowerDefense::Sift::Sift()
	:Card("Sift", CardType::SKILL, 30, "sift", "siftUpgraded")
{
}

void TowerDefense::Sift::Play()
{
	auto hand = Player::Get().GetHand();
	for(int i = 0; i < 4; i++)
		hand->DrawCard();
	if (m_Upgraded)
		hand->DiscardCards(2);
	else
		hand->DiscardCards(3);
}

std::shared_ptr<TowerDefense::Card> TowerDefense::Sift::Clone()
{
	auto card = std::make_shared<Sift>();
	if (m_Upgraded)
		card->Upgrade();
	return card;
}