#include "pch.h"
#include "SkillCards.h"
#include "core/Player.h"

TowerDefense::Attain::Attain()
	:Card("Attain", CardType::SKILL, 30, "attain", "attainUpgraded")
{
}

bool TowerDefense::Attain::Play()
{
	auto hand = Player::Get().GetHand();
	for(int i = 0; i < 3; i++)
		hand->DrawCard();
	if (m_Upgraded)
		hand->DrawCard();

	return true;
}

std::shared_ptr<TowerDefense::Card> TowerDefense::Attain::Clone()
{
	auto card = std::make_shared<Attain>();
	if (m_Upgraded)
		card->Upgrade();
	return card;
}