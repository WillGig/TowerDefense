#include "pch.h"
#include "Curses.h"
#include "core/Player.h"

TowerDefense::Flames::Flames()
	:Card("Flames", CardType::CURSE, 0, "Flames", "FlamesUpgraded")
{
}

bool TowerDefense::Flames::Play()
{
	Player::Get().ChangeHealth(-1);
	Player::Get().GetHand()->DrawCard();
	if(m_Upgraded)
		Player::Get().GetHand()->DrawCard();
	return true;
}

std::shared_ptr<TowerDefense::Card> TowerDefense::Flames::Clone()
{
	auto card = std::make_shared<Flames>();
	if (m_Upgraded)
		card->Upgrade();
	return card;
}