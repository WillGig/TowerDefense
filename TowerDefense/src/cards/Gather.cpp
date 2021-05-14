#include "pch.h"
#include "SkillCards.h"
#include "core/Player.h"

TowerDefense::Gather::Gather()
	:Card("Gather", CardType::SKILL, 0, "gather", "gatherUpgraded")
{
}

void TowerDefense::Gather::Play()
{
	Player& player = Player::Get();
	int changeAmount = m_Upgraded ? 50 : 40;
	int handSize = player.GetHand()->GetSize();

	if (handSize > 2)
	{
		player.ChangeEnergy(changeAmount * 3);
		player.GetHand()->DiscardCards(3);
	}	
	else
	{
		player.ChangeEnergy(changeAmount * handSize);
		player.GetHand()->DiscardCards(handSize);
	}
}

std::shared_ptr<TowerDefense::Card> TowerDefense::Gather::Clone()
{
	auto card = std::make_shared<Gather>();
	if (m_Upgraded)
		card->Upgrade();
	return card;
}