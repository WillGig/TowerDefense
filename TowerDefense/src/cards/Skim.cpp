#include "pch.h"
#include "SkillCards.h"
#include "core/Player.h"

TowerDefense::Skim::Skim()
	:Card("Skim", CardType::SKILL, 0, "skim", "skimUpgraded")
{
}

void TowerDefense::Skim::Play()
{
	auto hand = Player::Get().GetHand();
	for (int i = 0; i < 3; i++)
		hand->DrawCard();
	if (m_Upgraded)
		hand->DiscardCards(2);
	else
		hand->DiscardCards(3);
}

std::shared_ptr<TowerDefense::Card> TowerDefense::Skim::Clone()
{
	auto card = std::make_shared<Skim>();
	if (m_Upgraded)
		card->Upgrade();
	return card;
}