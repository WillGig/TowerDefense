#include "pch.h"
#include "SkillCards.h"
#include "core/Player.h"

TowerDefense::Reflect::Reflect()
	:Card("Reflect", CardType::SKILL, 20, "reflect", "reflectUpgraded")
{
}

void TowerDefense::Reflect::Play()
{
	auto hand = Player::Get().GetHand();
	for (int i = 0; i < 3; i++)
		hand->DrawCard();
	if (m_Upgraded)
		hand->DrawCard();
	
	hand->DiscardCards(1);
}

std::shared_ptr<TowerDefense::Card> TowerDefense::Reflect::Clone()
{
	auto card = std::make_shared<Reflect>();
	if (m_Upgraded)
		card->Upgrade();
	return card;
}