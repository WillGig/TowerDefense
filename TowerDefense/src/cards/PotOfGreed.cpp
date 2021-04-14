#include "pch.h"
#include "PotOfGreed.h"
#include "core/Player.h"

TowerDefense::PotOfGreed::PotOfGreed()
	:Card("Pot of Greed", 20, "res/textures/potOfGreed.png", "res/textures/potOfGreedUpgraded.png")
{
}

void TowerDefense::PotOfGreed::Play()
{
	if (Player::Get().GetEnergy() >= GetCost()) {
		Player::Get().GetHand()->DrawCard();
		Player::Get().GetHand()->DrawCard();
		if (m_Upgraded)
			Player::Get().GetHand()->DrawCard();
		Card::Play();
	}
}

std::shared_ptr<TowerDefense::Card> TowerDefense::PotOfGreed::Clone()
{
	auto card = std::make_shared<PotOfGreed>();
	if (m_Upgraded)
		card->Upgrade();
	return card;
}